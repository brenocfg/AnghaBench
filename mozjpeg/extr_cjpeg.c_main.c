#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_error_mgr {scalar_t__ num_warnings; int /*<<< orphan*/  last_addon_message; int /*<<< orphan*/  first_addon_message; int /*<<< orphan*/  addon_message_table; } ;
struct jpeg_compress_struct {scalar_t__ next_scanline; scalar_t__ image_height; scalar_t__ write_Adobe_marker; scalar_t__ write_JFIF_header; int /*<<< orphan*/  in_color_space; int /*<<< orphan*/  err; } ;
struct cdjpeg_progress_mgr {int dummy; } ;
typedef  TYPE_1__* jpeg_saved_marker_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  TYPE_2__* cjpeg_source_ptr ;
struct TYPE_8__ {int /*<<< orphan*/  (* finish_input ) (struct jpeg_compress_struct*,TYPE_2__*) ;int /*<<< orphan*/  buffer; int /*<<< orphan*/  plane_pointer; int /*<<< orphan*/  (* get_pixel_rows ) (struct jpeg_compress_struct*,TYPE_2__*) ;TYPE_1__* marker_list; int /*<<< orphan*/  (* start_input ) (struct jpeg_compress_struct*,TYPE_2__*) ;int /*<<< orphan*/ * input_file; } ;
struct TYPE_7__ {scalar_t__ marker; int data_length; int /*<<< orphan*/ * data; struct TYPE_7__* next; } ;
typedef  unsigned char JOCTET ;
typedef  int /*<<< orphan*/  JDIMENSION ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  EXIT_WARNING ; 
 int /*<<< orphan*/  FALSE ; 
 int GETJOCTET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JCS_RGB ; 
 int /*<<< orphan*/  JMSG_FIRSTADDONCODE ; 
 int /*<<< orphan*/  JMSG_LASTADDONCODE ; 
 scalar_t__ JPEG_APP0 ; 
 int /*<<< orphan*/  READ_BINARY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_BINARY ; 
 int ccommand (char***) ; 
 int /*<<< orphan*/  cdjpeg_message_table ; 
 scalar_t__ copy_markers ; 
 int /*<<< orphan*/  end_progress_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (unsigned char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* icc_filename ; 
 scalar_t__ is_jpeg ; 
 int /*<<< orphan*/  jpeg_create_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_default_colorspace (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_mem_dest (struct jpeg_compress_struct*,unsigned char**,unsigned long*) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_start_compress (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_std_error (struct jpeg_error_mgr*) ; 
 int /*<<< orphan*/  jpeg_stdio_dest (struct jpeg_compress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_write_icc_profile (struct jpeg_compress_struct*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  jpeg_write_marker (struct jpeg_compress_struct*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jpeg_write_raw_data (struct jpeg_compress_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_write_scanlines (struct jpeg_compress_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (long) ; 
 scalar_t__ memdst ; 
 char* outfilename ; 
 int parse_switches (struct jpeg_compress_struct*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* progname ; 
 int /*<<< orphan*/ * read_stdin () ; 
 TYPE_2__* select_file_type (struct jpeg_compress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_progress_monitor (int /*<<< orphan*/ ,struct cdjpeg_progress_mgr*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stub1 (struct jpeg_compress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct jpeg_compress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (struct jpeg_compress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/ * write_stdout () ; 

int
main(int argc, char **argv)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
#ifdef PROGRESS_REPORT
  struct cdjpeg_progress_mgr progress;
#endif
  int file_index;
  cjpeg_source_ptr src_mgr;
  FILE *input_file;
  FILE *icc_file;
  JOCTET *icc_profile = NULL;
  long icc_len = 0;
  FILE *output_file = NULL;
  unsigned char *outbuffer = NULL;
  unsigned long outsize = 0;
  JDIMENSION num_scanlines;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  progname = argv[0];
  if (progname == NULL || progname[0] == 0)
    progname = "cjpeg";         /* in case C library doesn't provide it */

  /* Initialize the JPEG compression object with default error handling. */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  /* Add some application-specific error messages (from cderror.h) */
  jerr.addon_message_table = cdjpeg_message_table;
  jerr.first_addon_message = JMSG_FIRSTADDONCODE;
  jerr.last_addon_message = JMSG_LASTADDONCODE;

  /* Initialize JPEG parameters.
   * Much of this may be overridden later.
   * In particular, we don't yet know the input file's color space,
   * but we need to provide some value for jpeg_set_defaults() to work.
   */

  cinfo.in_color_space = JCS_RGB; /* arbitrary guess */
  jpeg_set_defaults(&cinfo);

  /* Scan command line to find file names.
   * It is convenient to use just one switch-parsing routine, but the switch
   * values read here are ignored; we will rescan the switches after opening
   * the input file.
   */

  file_index = parse_switches(&cinfo, argc, argv, 0, FALSE);

#ifdef TWO_FILE_COMMANDLINE
  if (!memdst) {
    /* Must have either -outfile switch or explicit output file name */
    if (outfilename == NULL) {
      if (file_index != argc - 2) {
        fprintf(stderr, "%s: must name one input and one output file\n",
                progname);
        usage();
      }
      outfilename = argv[file_index + 1];
    } else {
      if (file_index != argc - 1) {
        fprintf(stderr, "%s: must name one input and one output file\n",
                progname);
        usage();
      }
    }
  }
#else
  /* Unix style: expect zero or one file name */
  if (file_index < argc - 1) {
    fprintf(stderr, "%s: only one input file\n", progname);
    usage();
  }
#endif /* TWO_FILE_COMMANDLINE */

  /* Open the input file. */
  if (file_index < argc) {
    if ((input_file = fopen(argv[file_index], READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, argv[file_index]);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default input file is stdin */
    input_file = read_stdin();
  }

  /* Open the output file. */
  if (outfilename != NULL) {
    if ((output_file = fopen(outfilename, WRITE_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, outfilename);
      exit(EXIT_FAILURE);
    }
  } else if (!memdst) {
    /* default output file is stdout */
    output_file = write_stdout();
  }

  if (icc_filename != NULL) {
    if ((icc_file = fopen(icc_filename, READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, icc_filename);
      exit(EXIT_FAILURE);
    }
    if (fseek(icc_file, 0, SEEK_END) < 0 ||
        (icc_len = ftell(icc_file)) < 1 ||
        fseek(icc_file, 0, SEEK_SET) < 0) {
      fprintf(stderr, "%s: can't determine size of %s\n", progname,
              icc_filename);
      exit(EXIT_FAILURE);
    }
    if ((icc_profile = (JOCTET *)malloc(icc_len)) == NULL) {
      fprintf(stderr, "%s: can't allocate memory for ICC profile\n", progname);
      fclose(icc_file);
      exit(EXIT_FAILURE);
    }
    if (fread(icc_profile, icc_len, 1, icc_file) < 1) {
      fprintf(stderr, "%s: can't read ICC profile from %s\n", progname,
              icc_filename);
      free(icc_profile);
      fclose(icc_file);
      exit(EXIT_FAILURE);
    }
    fclose(icc_file);
  }

#ifdef PROGRESS_REPORT
  start_progress_monitor((j_common_ptr)&cinfo, &progress);
#endif

  /* Figure out the input file format, and set up to read it. */
  src_mgr = select_file_type(&cinfo, input_file);
  src_mgr->input_file = input_file;

  /* Read the input file header to obtain file size & colorspace. */
  (*src_mgr->start_input) (&cinfo, src_mgr);

  /* Now that we know input colorspace, fix colorspace-dependent defaults */
#if JPEG_RAW_READER
  if (!is_jpeg)
#endif
  jpeg_default_colorspace(&cinfo);

  /* Adjust default compression parameters by re-parsing the options */
  file_index = parse_switches(&cinfo, argc, argv, 0, TRUE);

  /* Specify data destination for compression */
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
  if (memdst)
    jpeg_mem_dest(&cinfo, &outbuffer, &outsize);
  else
#endif
    jpeg_stdio_dest(&cinfo, output_file);

  /* Start compressor */
  jpeg_start_compress(&cinfo, TRUE);

  /* Copy metadata */
  if (copy_markers) {
    jpeg_saved_marker_ptr marker;
    
    /* In the current implementation, we don't actually need to examine the
     * option flag here; we just copy everything that got saved.
     * But to avoid confusion, we do not output JFIF and Adobe APP14 markers
     * if the encoder library already wrote one.
     */
    for (marker = src_mgr->marker_list; marker != NULL; marker = marker->next) {
      if (cinfo.write_JFIF_header &&
          marker->marker == JPEG_APP0 &&
          marker->data_length >= 5 &&
          GETJOCTET(marker->data[0]) == 0x4A &&
          GETJOCTET(marker->data[1]) == 0x46 &&
          GETJOCTET(marker->data[2]) == 0x49 &&
          GETJOCTET(marker->data[3]) == 0x46 &&
          GETJOCTET(marker->data[4]) == 0)
        continue;                       /* reject duplicate JFIF */
      if (cinfo.write_Adobe_marker &&
          marker->marker == JPEG_APP0+14 &&
          marker->data_length >= 5 &&
          GETJOCTET(marker->data[0]) == 0x41 &&
          GETJOCTET(marker->data[1]) == 0x64 &&
          GETJOCTET(marker->data[2]) == 0x6F &&
          GETJOCTET(marker->data[3]) == 0x62 &&
          GETJOCTET(marker->data[4]) == 0x65)
        continue;                       /* reject duplicate Adobe */
      jpeg_write_marker(&cinfo, marker->marker, marker->data,
                        marker->data_length);
    }
  }
  if (icc_profile != NULL)
    jpeg_write_icc_profile(&cinfo, icc_profile, (unsigned int)icc_len);
  
  /* Process data */
  while (cinfo.next_scanline < cinfo.image_height) {
    num_scanlines = (*src_mgr->get_pixel_rows) (&cinfo, src_mgr);
#if JPEG_RAW_READER
    if (is_jpeg)
      (void) jpeg_write_raw_data(&cinfo, src_mgr->plane_pointer, num_scanlines);
    else
#endif
    (void) jpeg_write_scanlines(&cinfo, src_mgr->buffer, num_scanlines);
  }

  /* Finish compression and release memory */
  (*src_mgr->finish_input) (&cinfo, src_mgr);
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  /* Close files, if we opened them */
  if (input_file != stdin)
    fclose(input_file);
  if (output_file != stdout && output_file != NULL)
    fclose(output_file);

#ifdef PROGRESS_REPORT
  end_progress_monitor((j_common_ptr)&cinfo);
#endif

  if (memdst) {
    fprintf(stderr, "Compressed size:  %lu bytes\n", outsize);
    if (outbuffer != NULL)
      free(outbuffer);
  }

  if (icc_profile != NULL)
    free(icc_profile);

  /* All done. */
  exit(jerr.num_warnings ? EXIT_WARNING : EXIT_SUCCESS);
  return 0;                     /* suppress no-return-value warnings */
}