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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  READ_BINARY ; 
 int ccommand (char***) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/ * infile ; 
 scalar_t__ keymatch (char*,char*,int) ; 
 scalar_t__* progname ; 
 int /*<<< orphan*/  scan_JPEG_header (int,int) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  usage () ; 

int
main (int argc, char **argv)
{
  int argn;
  char * arg;
  int verbose = 0, raw = 0;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  progname = argv[0];
  if (progname == NULL || progname[0] == 0)
    progname = "rdjpgcom";	/* in case C library doesn't provide it */

  /* Parse switches, if any */
  for (argn = 1; argn < argc; argn++) {
    arg = argv[argn];
    if (arg[0] != '-')
      break;			/* not switch, must be file name */
    arg++;			/* advance over '-' */
    if (keymatch(arg, "verbose", 1)) {
      verbose++;
    } else if (keymatch(arg, "raw", 1)) {
      raw = 1;
    } else
      usage();
  }

  /* Open the input file. */
  /* Unix style: expect zero or one file name */
  if (argn < argc-1) {
    fprintf(stderr, "%s: only one input file\n", progname);
    usage();
  }
  if (argn < argc) {
    if ((infile = fopen(argv[argn], READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, argv[argn]);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default input file is stdin */
#ifdef USE_SETMODE		/* need to hack file mode? */
    setmode(fileno(stdin), O_BINARY);
#endif
#ifdef USE_FDOPEN		/* need to re-open in binary mode? */
    if ((infile = fdopen(fileno(stdin), READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open stdin\n", progname);
      exit(EXIT_FAILURE);
    }
#else
    infile = stdin;
#endif
  }

  /* Scan the JPEG headers. */
  (void) scan_JPEG_header(verbose, raw);

  /* All done. */
  exit(EXIT_SUCCESS);
  return 0;			/* suppress no-return-value warnings */
}