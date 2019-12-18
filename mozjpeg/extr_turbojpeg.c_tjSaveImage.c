#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int image_width; int image_height; int scale_num; int scale_denom; int output_scanline; int output_height; TYPE_2__* mem; int /*<<< orphan*/  global_state; int /*<<< orphan*/  out_color_space; } ;
struct TYPE_16__ {int /*<<< orphan*/  setjmp_buffer; } ;
struct TYPE_18__ {TYPE_4__ dinfo; TYPE_1__ jerr; } ;
typedef  TYPE_3__ tjinstance ;
typedef  int /*<<< orphan*/ * tjhandle ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  TYPE_5__* djpeg_dest_ptr ;
typedef  int boolean ;
struct TYPE_20__ {int /*<<< orphan*/  (* finish_output ) (TYPE_4__*,TYPE_5__*) ;int /*<<< orphan*/  (* put_pixel_rows ) (TYPE_4__*,TYPE_5__*,int) ;int /*<<< orphan*/ * buffer; int /*<<< orphan*/  (* start_output ) (TYPE_4__*,TYPE_5__*) ;int /*<<< orphan*/ * output_file; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* realize_virt_arrays ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DSTATE_READY ; 
 int /*<<< orphan*/  FALSE ; 
 int TJFLAG_BOTTOMUP ; 
 int TJ_NUMPF ; 
 int /*<<< orphan*/  _throwg (char*) ; 
 int /*<<< orphan*/  _throwunix (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 TYPE_5__* jinit_write_bmp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* jinit_write_ppm (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/ * pf2cs ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  tjDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tjInitDecompress () ; 
 int* tjPixelSize ; 

int tjSaveImage(const char *filename, unsigned char *buffer,
                          int width, int pitch, int height, int pixelFormat,
                          int flags)
{
  int retval = 0;
  tjhandle handle = NULL;
  tjinstance *this;
  j_decompress_ptr dinfo = NULL;
  djpeg_dest_ptr dst;
  FILE *file = NULL;
  char *ptr = NULL;
  boolean invert;

  if (!filename || !buffer || width < 1 || pitch < 0 || height < 1 ||
      pixelFormat < 0 || pixelFormat >= TJ_NUMPF)
    _throwg("tjSaveImage(): Invalid argument");

  if ((handle = tjInitDecompress()) == NULL)
    return -1;
  this = (tjinstance *)handle;
  dinfo = &this->dinfo;

  if ((file = fopen(filename, "wb")) == NULL)
    _throwunix("tjSaveImage(): Cannot open output file");

  if (setjmp(this->jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error. */
    retval = -1;  goto bailout;
  }

  this->dinfo.out_color_space = pf2cs[pixelFormat];
  dinfo->image_width = width;  dinfo->image_height = height;
  dinfo->global_state = DSTATE_READY;
  dinfo->scale_num = dinfo->scale_denom = 1;

  ptr = strrchr(filename, '.');
  if (ptr && !strcasecmp(ptr, ".bmp")) {
    if ((dst = jinit_write_bmp(dinfo, FALSE, FALSE)) == NULL)
      _throwg("tjSaveImage(): Could not initialize bitmap writer");
    invert = (flags & TJFLAG_BOTTOMUP) == 0;
  } else {
    if ((dst = jinit_write_ppm(dinfo)) == NULL)
      _throwg("tjSaveImage(): Could not initialize PPM writer");
    invert = (flags & TJFLAG_BOTTOMUP) != 0;
  }

  dst->output_file = file;
  (*dst->start_output) (dinfo, dst);
  (*dinfo->mem->realize_virt_arrays) ((j_common_ptr)dinfo);

  if (pitch == 0) pitch = width * tjPixelSize[pixelFormat];

  while (dinfo->output_scanline < dinfo->output_height) {
    unsigned char *rowptr;

    if (invert)
      rowptr = &buffer[(height - dinfo->output_scanline - 1) * pitch];
    else
      rowptr = &buffer[dinfo->output_scanline * pitch];
    memcpy(dst->buffer[0], rowptr, width * tjPixelSize[pixelFormat]);
    (*dst->put_pixel_rows) (dinfo, dst, 1);
    dinfo->output_scanline++;
  }

  (*dst->finish_output) (dinfo, dst);

bailout:
  if (handle) tjDestroy(handle);
  if (file) fclose(file);
	return retval;
}