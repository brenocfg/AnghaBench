#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jpeg_error_mgr {int dummy; } ;
struct jpeg_compress_struct {int image_width; int image_height; int input_components; int next_scanline; void* optimize_coding; TYPE_1__* comp_info; void* raw_data_in; int /*<<< orphan*/  in_color_space; int /*<<< orphan*/  err; } ;
struct TYPE_2__ {int h_samp_factor; int v_samp_factor; int dc_tbl_no; int ac_tbl_no; int quant_tbl_no; } ;
typedef  unsigned char* JSAMPROW ;
typedef  unsigned char JSAMPLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_YCbCr ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 void* TRUE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  extend_edge (unsigned char*,int,int,unsigned char*,int,int,int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (unsigned char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_create_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_quality (struct jpeg_compress_struct*,long,void*) ; 
 int /*<<< orphan*/  jpeg_start_compress (struct jpeg_compress_struct*,void*) ; 
 int /*<<< orphan*/  jpeg_std_error (struct jpeg_error_mgr*) ; 
 int /*<<< orphan*/  jpeg_stdio_dest (struct jpeg_compress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_write_raw_data (struct jpeg_compress_struct*,unsigned char***,int) ; 
 unsigned char* malloc (int) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,int /*<<< orphan*/ *,int) ; 

int main(int argc, char *argv[]) {
  long quality;
  int matches;
  int luma_width;
  int luma_height;
  int chroma_width;
  int chroma_height;
  int frame_width;
  int frame_height;
  const char *yuv_path;
  const char *jpg_path;
  FILE *yuv_fd;
  size_t yuv_size;
  unsigned char *yuv_buffer;
  JSAMPLE *jpg_buffer;
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *jpg_fd;
  JSAMPROW yrow_pointer[16];
  JSAMPROW cbrow_pointer[8];
  JSAMPROW crrow_pointer[8];
  JSAMPROW *plane_pointer[3];
  int y;

  if (argc != 5) {
    fprintf(stderr, "Required arguments:\n");
    fprintf(stderr, "1. JPEG quality value, 0-100\n");
    fprintf(stderr, "2. Image size (e.g. '512x512')\n");
    fprintf(stderr, "3. Path to YUV input file\n");
    fprintf(stderr, "4. Path to JPG output file\n");
    return 1;
  }

  errno = 0;

  quality = strtol(argv[1], NULL, 10);
  if (errno != 0 || quality < 0 || quality > 100) {
    fprintf(stderr, "Invalid JPEG quality value!\n");
    return 1;
  }

  matches = sscanf(argv[2], "%dx%d", &luma_width, &luma_height);
  if (matches != 2) {
    fprintf(stderr, "Invalid image size input!\n");
    return 1;
  }
  if (luma_width <= 0 || luma_height <= 0) {
    fprintf(stderr, "Invalid image size input!\n");
    return 1;
  }

  chroma_width = (luma_width + 1) >> 1;
  chroma_height = (luma_height + 1) >> 1;

  /* Will check these for validity when opening via 'fopen'. */
  yuv_path = argv[3];
  jpg_path = argv[4];

  yuv_fd = fopen(yuv_path, "r");
  if (!yuv_fd) {
    fprintf(stderr, "Invalid path to YUV file!\n");
    return 1;
  }

  fseek(yuv_fd, 0, SEEK_END);
  yuv_size = ftell(yuv_fd);
  fseek(yuv_fd, 0, SEEK_SET);

  /* Check that the file size matches 4:2:0 yuv. */
  if (yuv_size !=
   (size_t)luma_width*luma_height + 2*chroma_width*chroma_height) {
    fclose(yuv_fd);
    fprintf(stderr, "Unexpected input format!\n");
    return 1;
  }

  yuv_buffer = malloc(yuv_size);
  if (!yuv_buffer) {
    fclose(yuv_fd);
    fprintf(stderr, "Memory allocation failure!\n");
    return 1;
  }

  if (fread(yuv_buffer, yuv_size, 1, yuv_fd) != 1) {
    fprintf(stderr, "Error reading yuv file\n");
  };

  fclose(yuv_fd);

  frame_width = (luma_width + (16 - 1)) & ~(16 - 1);
  frame_height = (luma_height + (16 - 1)) & ~(16 - 1);

  jpg_buffer =
   malloc(frame_width*frame_height + 2*(frame_width/2)*(frame_height/2));
  if (!jpg_buffer) {
    free(yuv_buffer);
    fprintf(stderr, "Memory allocation failure!\n");
    return 1;
  }

  extend_edge(jpg_buffer, frame_width, frame_height,
   yuv_buffer, luma_width, luma_height, chroma_width, chroma_height);

  free(yuv_buffer);

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  jpg_fd = fopen(jpg_path, "wb");
  if (!jpg_fd) {    
    free(jpg_buffer);
    fprintf(stderr, "Invalid path to JPEG file!\n");
    return 1;
  }

  jpeg_stdio_dest(&cinfo, jpg_fd);

  cinfo.image_width = luma_width;
  cinfo.image_height = luma_height;
  cinfo.input_components = 3;

  cinfo.in_color_space = JCS_YCbCr;
  jpeg_set_defaults(&cinfo);

  cinfo.raw_data_in = TRUE;

  cinfo.comp_info[0].h_samp_factor = 2;
  cinfo.comp_info[0].v_samp_factor = 2;
  cinfo.comp_info[0].dc_tbl_no = 0;
  cinfo.comp_info[0].ac_tbl_no = 0;
  cinfo.comp_info[0].quant_tbl_no = 0;

  cinfo.comp_info[1].h_samp_factor = 1;
  cinfo.comp_info[1].v_samp_factor = 1;
  cinfo.comp_info[1].dc_tbl_no = 1;
  cinfo.comp_info[1].ac_tbl_no = 1;
  cinfo.comp_info[1].quant_tbl_no = 1;

  cinfo.comp_info[2].h_samp_factor = 1;
  cinfo.comp_info[2].v_samp_factor = 1;
  cinfo.comp_info[2].dc_tbl_no = 1;
  cinfo.comp_info[2].ac_tbl_no = 1;
  cinfo.comp_info[2].quant_tbl_no = 1;

  jpeg_set_quality(&cinfo, quality, TRUE);
  cinfo.optimize_coding = TRUE;

  jpeg_start_compress(&cinfo, TRUE);

  plane_pointer[0] = yrow_pointer;
  plane_pointer[1] = cbrow_pointer;
  plane_pointer[2] = crrow_pointer;

  while (cinfo.next_scanline < cinfo.image_height) {
    int scanline;
    scanline = cinfo.next_scanline;

    for (y = 0; y < 16; y++) {
      yrow_pointer[y] = &jpg_buffer[frame_width*(scanline + y)];
    }
    for (y = 0; y < 8; y++) {
      cbrow_pointer[y] = &jpg_buffer[frame_width*frame_height +
       (frame_width/2)*((scanline/2) + y)];
      crrow_pointer[y] = &jpg_buffer[frame_width*frame_height +
       (frame_width/2)*(frame_height/2) + (frame_width/2)*((scanline/2) + y)];
    }
    jpeg_write_raw_data(&cinfo, plane_pointer, 16);
  }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  free(jpg_buffer);
  fclose(jpg_fd);

  return 0;
}