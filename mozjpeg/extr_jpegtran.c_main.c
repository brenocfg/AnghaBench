#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jpeg_error_mgr {scalar_t__ num_warnings; int /*<<< orphan*/  trace_level; } ;
struct jpeg_decompress_struct {TYPE_1__* mem; void* err; } ;
struct jpeg_compress_struct {TYPE_2__* mem; void* err; } ;
struct cdjpeg_progress_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  jvirt_barray_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_4__ {int /*<<< orphan*/  max_memory_to_use; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_memory_to_use; } ;
typedef  unsigned char JOCTET ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  EXIT_WARNING ; 
 scalar_t__ FALSE ; 
 size_t INPUT_BUF_SIZE ; 
 scalar_t__ JCOPYOPT_ALL ; 
 scalar_t__ JCOPYOPT_ALL_EXCEPT_ICC ; 
 scalar_t__ JCP_MAX_COMPRESSION ; 
 size_t JFREAD (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t JFWRITE (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  JINT_COMPRESS_PROFILE ; 
 int /*<<< orphan*/  READ_BINARY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WRITE_BINARY ; 
 int ccommand (char***) ; 
 scalar_t__ copyoption ; 
 int /*<<< orphan*/  end_progress_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__*,...) ; 
 int fread (unsigned char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* icc_filename ; 
 int /*<<< orphan*/  jcopy_markers_execute (struct jpeg_decompress_struct*,struct jpeg_compress_struct*,scalar_t__) ; 
 int /*<<< orphan*/  jcopy_markers_setup (struct jpeg_decompress_struct*,scalar_t__) ; 
 scalar_t__ jpeg_c_get_int_param (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ jpeg_c_int_param_supported (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_copy_critical_parameters (struct jpeg_decompress_struct*,struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_create_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_create_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_mem_dest (struct jpeg_compress_struct*,unsigned char**,unsigned long*) ; 
 int /*<<< orphan*/  jpeg_mem_src (struct jpeg_decompress_struct*,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/ * jpeg_read_coefficients (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_read_header (struct jpeg_decompress_struct*,scalar_t__) ; 
 void* jpeg_std_error (struct jpeg_error_mgr*) ; 
 int /*<<< orphan*/  jpeg_stdio_dest (struct jpeg_compress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_stdio_src (struct jpeg_decompress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_write_coefficients (struct jpeg_compress_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_write_icc_profile (struct jpeg_compress_struct*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/ * jtransform_adjust_parameters (struct jpeg_decompress_struct*,struct jpeg_compress_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jtransform_execute_transformation (struct jpeg_decompress_struct*,struct jpeg_compress_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jtransform_request_workspace (struct jpeg_decompress_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (long) ; 
 scalar_t__ memsrc ; 
 char* outfilename ; 
 int parse_switches (struct jpeg_compress_struct*,int,char**,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ prefer_smallest ; 
 scalar_t__* progname ; 
 int /*<<< orphan*/ * read_stdin () ; 
 scalar_t__ realloc (unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  start_progress_monitor (int /*<<< orphan*/ ,struct cdjpeg_progress_mgr*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  transformoption ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/ * write_stdout () ; 

int
main (int argc, char **argv)
{
  struct jpeg_decompress_struct srcinfo;
  struct jpeg_compress_struct dstinfo;
  struct jpeg_error_mgr jsrcerr, jdsterr;
#ifdef PROGRESS_REPORT
  struct cdjpeg_progress_mgr progress;
#endif
  jvirt_barray_ptr *src_coef_arrays;
  jvirt_barray_ptr *dst_coef_arrays;
  int file_index;
  /* We assume all-in-memory processing and can therefore use only a
   * single file pointer for sequential input and output operation.
   */
  FILE *fp;
  unsigned char *inbuffer = NULL;
  unsigned long insize = 0;
  unsigned char *outbuffer = NULL;
  unsigned long outsize = 0;
  FILE *icc_file;
  JOCTET *icc_profile = NULL;
  long icc_len = 0;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  progname = argv[0];
  if (progname == NULL || progname[0] == 0)
    progname = "jpegtran";      /* in case C library doesn't provide it */

  /* Initialize the JPEG decompression object with default error handling. */
  srcinfo.err = jpeg_std_error(&jsrcerr);
  jpeg_create_decompress(&srcinfo);
  /* Initialize the JPEG compression object with default error handling. */
  dstinfo.err = jpeg_std_error(&jdsterr);
  jpeg_create_compress(&dstinfo);

  /* Scan command line to find file names.
   * It is convenient to use just one switch-parsing routine, but the switch
   * values read here are mostly ignored; we will rescan the switches after
   * opening the input file.  Also note that most of the switches affect the
   * destination JPEG object, so we parse into that and then copy over what
   * needs to affects the source too.
   */

  file_index = parse_switches(&dstinfo, argc, argv, 0, FALSE);
  jsrcerr.trace_level = jdsterr.trace_level;
  srcinfo.mem->max_memory_to_use = dstinfo.mem->max_memory_to_use;

#ifdef TWO_FILE_COMMANDLINE
  /* Must have either -outfile switch or explicit output file name */
  if (outfilename == NULL) {
    if (file_index != argc-2) {
      fprintf(stderr, "%s: must name one input and one output file\n",
              progname);
      usage();
    }
    outfilename = argv[file_index+1];
  } else {
    if (file_index != argc-1) {
      fprintf(stderr, "%s: must name one input and one output file\n",
              progname);
      usage();
    }
  }
#else
  /* Unix style: expect zero or one file name */
  if (file_index < argc-1) {
    fprintf(stderr, "%s: only one input file\n", progname);
    usage();
  }
#endif /* TWO_FILE_COMMANDLINE */

  /* Open the input file. */
  if (file_index < argc) {
    if ((fp = fopen(argv[file_index], READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s for reading\n", progname,
              argv[file_index]);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default input file is stdin */
    fp = read_stdin();
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
    if (copyoption == JCOPYOPT_ALL)
      copyoption = JCOPYOPT_ALL_EXCEPT_ICC;
  }

#ifdef PROGRESS_REPORT
  start_progress_monitor((j_common_ptr) &dstinfo, &progress);
#endif

  /* Specify data source for decompression */
  if (jpeg_c_int_param_supported(&dstinfo, JINT_COMPRESS_PROFILE) &&
      jpeg_c_get_int_param(&dstinfo, JINT_COMPRESS_PROFILE)
        == JCP_MAX_COMPRESSION)
    memsrc = TRUE; /* needed to revert to original */
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
  if (memsrc) {
    size_t nbytes;
    do {
      inbuffer = (unsigned char *)realloc(inbuffer, insize + INPUT_BUF_SIZE);
      if (inbuffer == NULL) {
        fprintf(stderr, "%s: memory allocation failure\n", progname);
        exit(EXIT_FAILURE);
      }
      nbytes = JFREAD(fp, &inbuffer[insize], INPUT_BUF_SIZE);
      if (nbytes < INPUT_BUF_SIZE && ferror(fp)) {
        if (file_index < argc)
          fprintf(stderr, "%s: can't read from %s\n", progname,
                  argv[file_index]);
        else
          fprintf(stderr, "%s: can't read from stdin\n", progname);
      }
      insize += (unsigned long)nbytes;
    } while (nbytes == INPUT_BUF_SIZE);
    jpeg_mem_src(&srcinfo, inbuffer, insize);
  } else
#endif
  jpeg_stdio_src(&srcinfo, fp);

  /* Enable saving of extra markers that we want to copy */
  jcopy_markers_setup(&srcinfo, copyoption);

  /* Read file header */
  (void) jpeg_read_header(&srcinfo, TRUE);

  /* Any space needed by a transform option must be requested before
   * jpeg_read_coefficients so that memory allocation will be done right.
   */
#if TRANSFORMS_SUPPORTED
  /* Fail right away if -perfect is given and transformation is not perfect.
   */
  if (!jtransform_request_workspace(&srcinfo, &transformoption)) {
    fprintf(stderr, "%s: transformation is not perfect\n", progname);
    exit(EXIT_FAILURE);
  }
#endif

  /* Read source file as DCT coefficients */
  src_coef_arrays = jpeg_read_coefficients(&srcinfo);

  /* Initialize destination compression parameters from source values */
  jpeg_copy_critical_parameters(&srcinfo, &dstinfo);

  /* Adjust destination parameters if required by transform options;
   * also find out which set of coefficient arrays will hold the output.
   */
#if TRANSFORMS_SUPPORTED
  dst_coef_arrays = jtransform_adjust_parameters(&srcinfo, &dstinfo,
                                                 src_coef_arrays,
                                                 &transformoption);
#else
  dst_coef_arrays = src_coef_arrays;
#endif

  /* Close input file, if we opened it.
   * Note: we assume that jpeg_read_coefficients consumed all input
   * until JPEG_REACHED_EOI, and that jpeg_finish_decompress will
   * only consume more while (! cinfo->inputctl->eoi_reached).
   * We cannot call jpeg_finish_decompress here since we still need the
   * virtual arrays allocated from the source object for processing.
   */
  if (fp != stdin)
    fclose(fp);

  /* Open the output file. */
  if (outfilename != NULL) {
    if ((fp = fopen(outfilename, WRITE_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s for writing\n", progname,
              outfilename);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default output file is stdout */
    fp = write_stdout();
  }

  /* Adjust default compression parameters by re-parsing the options */
  file_index = parse_switches(&dstinfo, argc, argv, 0, TRUE);

  /* Specify data destination for compression */
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
  if (jpeg_c_int_param_supported(&dstinfo, JINT_COMPRESS_PROFILE) &&
      jpeg_c_get_int_param(&dstinfo, JINT_COMPRESS_PROFILE)
        == JCP_MAX_COMPRESSION)
    jpeg_mem_dest(&dstinfo, &outbuffer, &outsize);
  else
#endif
  jpeg_stdio_dest(&dstinfo, fp);

  /* Start compressor (note no image data is actually written here) */
  jpeg_write_coefficients(&dstinfo, dst_coef_arrays);

  /* Copy to the output file any extra markers that we want to preserve */
  jcopy_markers_execute(&srcinfo, &dstinfo, copyoption);

  if (icc_profile != NULL)
    jpeg_write_icc_profile(&dstinfo, icc_profile, (unsigned int)icc_len);

  /* Execute image transformation, if any */
#if TRANSFORMS_SUPPORTED
  jtransform_execute_transformation(&srcinfo, &dstinfo, src_coef_arrays,
                                    &transformoption);
#endif

  /* Finish compression and release memory */
  jpeg_finish_compress(&dstinfo);

#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
  if (jpeg_c_int_param_supported(&dstinfo, JINT_COMPRESS_PROFILE) &&
      jpeg_c_get_int_param(&dstinfo, JINT_COMPRESS_PROFILE)
        == JCP_MAX_COMPRESSION) {
    size_t nbytes;
    
    unsigned char *buffer = outbuffer;
    unsigned long size = outsize;
    if (prefer_smallest && insize < size) {
      size = insize;
      buffer = inbuffer;
    }

    nbytes = JFWRITE(fp, buffer, size);
    if (nbytes < size && ferror(fp)) {
      if (file_index < argc)
        fprintf(stderr, "%s: can't write to %s\n", progname,
                argv[file_index]);
      else
        fprintf(stderr, "%s: can't write to stdout\n", progname);
    }
  }
#endif
    
  jpeg_destroy_compress(&dstinfo);
  (void) jpeg_finish_decompress(&srcinfo);
  jpeg_destroy_decompress(&srcinfo);

  /* Close output file, if we opened it */
  if (fp != stdout)
    fclose(fp);

#ifdef PROGRESS_REPORT
  end_progress_monitor((j_common_ptr) &dstinfo);
#endif

  free(inbuffer);
  free(outbuffer);

  if (icc_profile != NULL)
    free(icc_profile);

  /* All done. */
  exit(jsrcerr.num_warnings + jdsterr.num_warnings ?
       EXIT_WARNING : EXIT_SUCCESS);
  return 0;                     /* suppress no-return-value warnings */
}