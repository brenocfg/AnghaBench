#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ERREXIT (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ MAX_COM_LENGTH ; 
 int M_COM ; 
 int /*<<< orphan*/  O_BINARY ; 
 char* READ_BINARY ; 
 char* WRITE_BINARY ; 
 int ccommand (char***) ; 
 int /*<<< orphan*/  copy_rest_of_file () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * infile ; 
 scalar_t__ keymatch (char*,char*,int) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/ * outfile ; 
 scalar_t__* progname ; 
 int scan_JPEG_header (int) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_1_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_2_bytes (unsigned int) ; 
 int /*<<< orphan*/  write_marker (int) ; 

int
main(int argc, char **argv)
{
  int argn;
  char *arg;
  int keep_COM = 1;
  char *comment_arg = NULL;
  FILE *comment_file = NULL;
  unsigned int comment_length = 0;
  int marker;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  progname = argv[0];
  if (progname == NULL || progname[0] == 0)
    progname = "wrjpgcom";      /* in case C library doesn't provide it */

  /* Parse switches, if any */
  for (argn = 1; argn < argc; argn++) {
    arg = argv[argn];
    if (arg[0] != '-')
      break;                    /* not switch, must be file name */
    arg++;                      /* advance over '-' */
    if (keymatch(arg, "replace", 1)) {
      keep_COM = 0;
    } else if (keymatch(arg, "cfile", 2)) {
      if (++argn >= argc) usage();
      if ((comment_file = fopen(argv[argn], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", progname, argv[argn]);
        exit(EXIT_FAILURE);
      }
    } else if (keymatch(arg, "comment", 1)) {
      if (++argn >= argc) usage();
      comment_arg = argv[argn];
      /* If the comment text starts with '"', then we are probably running
       * under MS-DOG and must parse out the quoted string ourselves.  Sigh.
       */
      if (comment_arg[0] == '"') {
        comment_arg = (char *)malloc((size_t)MAX_COM_LENGTH);
        if (comment_arg == NULL)
          ERREXIT("Insufficient memory");
        if (strlen(argv[argn]) + 2 >= (size_t)MAX_COM_LENGTH) {
          fprintf(stderr, "Comment text may not exceed %u bytes\n",
                  (unsigned int)MAX_COM_LENGTH);
          exit(EXIT_FAILURE);
        }
        strcpy(comment_arg, argv[argn] + 1);
        for (;;) {
          comment_length = (unsigned int)strlen(comment_arg);
          if (comment_length > 0 && comment_arg[comment_length - 1] == '"') {
            comment_arg[comment_length - 1] = '\0'; /* zap terminating quote */
            break;
          }
          if (++argn >= argc)
            ERREXIT("Missing ending quote mark");
          if (strlen(comment_arg) + strlen(argv[argn]) + 2 >=
              (size_t)MAX_COM_LENGTH) {
            fprintf(stderr, "Comment text may not exceed %u bytes\n",
                    (unsigned int)MAX_COM_LENGTH);
            exit(EXIT_FAILURE);
          }
          strcat(comment_arg, " ");
          strcat(comment_arg, argv[argn]);
        }
      } else if (strlen(argv[argn]) >= (size_t)MAX_COM_LENGTH) {
        fprintf(stderr, "Comment text may not exceed %u bytes\n",
                (unsigned int)MAX_COM_LENGTH);
        exit(EXIT_FAILURE);
      }
      comment_length = (unsigned int)strlen(comment_arg);
    } else
      usage();
  }

  /* Cannot use both -comment and -cfile. */
  if (comment_arg != NULL && comment_file != NULL)
    usage();
  /* If there is neither -comment nor -cfile, we will read the comment text
   * from stdin; in this case there MUST be an input JPEG file name.
   */
  if (comment_arg == NULL && comment_file == NULL && argn >= argc)
    usage();

  /* Open the input file. */
  if (argn < argc) {
    if ((infile = fopen(argv[argn], READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, argv[argn]);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default input file is stdin */
#ifdef USE_SETMODE              /* need to hack file mode? */
    setmode(fileno(stdin), O_BINARY);
#endif
#ifdef USE_FDOPEN               /* need to re-open in binary mode? */
    if ((infile = fdopen(fileno(stdin), READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open stdin\n", progname);
      exit(EXIT_FAILURE);
    }
#else
    infile = stdin;
#endif
  }

  /* Open the output file. */
#ifdef TWO_FILE_COMMANDLINE
  /* Must have explicit output file name */
  if (argn != argc - 2) {
    fprintf(stderr, "%s: must name one input and one output file\n", progname);
    usage();
  }
  if ((outfile = fopen(argv[argn + 1], WRITE_BINARY)) == NULL) {
    fprintf(stderr, "%s: can't open %s\n", progname, argv[argn + 1]);
    exit(EXIT_FAILURE);
  }
#else
  /* Unix style: expect zero or one file name */
  if (argn < argc - 1) {
    fprintf(stderr, "%s: only one input file\n", progname);
    usage();
  }
  /* default output file is stdout */
#ifdef USE_SETMODE              /* need to hack file mode? */
  setmode(fileno(stdout), O_BINARY);
#endif
#ifdef USE_FDOPEN               /* need to re-open in binary mode? */
  if ((outfile = fdopen(fileno(stdout), WRITE_BINARY)) == NULL) {
    fprintf(stderr, "%s: can't open stdout\n", progname);
    exit(EXIT_FAILURE);
  }
#else
  outfile = stdout;
#endif
#endif /* TWO_FILE_COMMANDLINE */

  /* Collect comment text from comment_file or stdin, if necessary */
  if (comment_arg == NULL) {
    FILE *src_file;
    int c;

    comment_arg = (char *)malloc((size_t)MAX_COM_LENGTH);
    if (comment_arg == NULL)
      ERREXIT("Insufficient memory");
    comment_length = 0;
    src_file = (comment_file != NULL ? comment_file : stdin);
    while ((c = getc(src_file)) != EOF) {
      if (comment_length >= (unsigned int)MAX_COM_LENGTH) {
        fprintf(stderr, "Comment text may not exceed %u bytes\n",
                (unsigned int)MAX_COM_LENGTH);
        exit(EXIT_FAILURE);
      }
      comment_arg[comment_length++] = (char)c;
    }
    if (comment_file != NULL)
      fclose(comment_file);
  }

  /* Copy JPEG headers until SOFn marker;
   * we will insert the new comment marker just before SOFn.
   * This (a) causes the new comment to appear after, rather than before,
   * existing comments; and (b) ensures that comments come after any JFIF
   * or JFXX markers, as required by the JFIF specification.
   */
  marker = scan_JPEG_header(keep_COM);
  /* Insert the new COM marker, but only if nonempty text has been supplied */
  if (comment_length > 0) {
    write_marker(M_COM);
    write_2_bytes(comment_length + 2);
    while (comment_length > 0) {
      write_1_byte(*comment_arg++);
      comment_length--;
    }
  }
  /* Duplicate the remainder of the source file.
   * Note that any COM markers occuring after SOF will not be touched.
   */
  write_marker(marker);
  copy_rest_of_file();

  /* All done. */
  exit(EXIT_SUCCESS);
  return 0;                     /* suppress no-return-value warnings */
}