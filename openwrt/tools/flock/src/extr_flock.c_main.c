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
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; TYPE_1__ it_value; } ;
struct itimerval {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; TYPE_1__ it_value; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
#define  EBADF 130 
#define  EINTR 129 
 int const EISDIR ; 
 int EMFILE ; 
 int ENFILE ; 
 int ENOLCK ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOF ; 
 int EROFS ; 
#define  EWOULDBLOCK 128 
 int EXIT_FAILURE ; 
 int EX_CANTCREAT ; 
 int EX_DATAERR ; 
 int EX_NOINPUT ; 
 int EX_OSERR ; 
 int EX_UNAVAILABLE ; 
 int EX_USAGE ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int LOCK_SH ; 
 int LOCK_UN ; 
 int O_CREAT ; 
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 char* PACKAGE_STRING ; 
 int R_OK ; 
 int /*<<< orphan*/  SA_RESETHAND ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int W_OK ; 
 char* _ (char*) ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  access (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int const errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ flock (int,int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  long_options ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,...) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 scalar_t__ optopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* program ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 char* strtotimeval (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  timeout_expired ; 
 int /*<<< orphan*/  timeout_handler ; 
 int /*<<< orphan*/  usage (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
  struct itimerval timeout, old_timer;
  int have_timeout = 0;
  int type = LOCK_EX;
  int block = 0;
  int fd = -1;
  int opt, ix;
  int do_close = 0;
  int err;
  int status;
  int open_flags = 0;
  char *eon;
  char **cmd_argv = NULL, *sh_c_argv[4];
  const char *filename = NULL;
  struct sigaction sa, old_sa;

  program = argv[0];

  if ( argc < 2 )
    usage(EX_USAGE);

  memset(&timeout, 0, sizeof timeout);

  optopt = 0;
  while ( (opt = getopt_long(argc, argv, "+sexnouw:hV?", long_options, &ix)) != EOF ) {
    switch(opt) {
    case 's':
      type = LOCK_SH;
      break;
    case 'e':
    case 'x':
      type = LOCK_EX;
      break;
    case 'u':
      type = LOCK_UN;
      break;
    case 'o':
      do_close = 1;
      break;
    case 'n':
      block = LOCK_NB;
      break;
    case 'w':
      have_timeout = 1;
      eon = strtotimeval(optarg, &timeout.it_value);
      if ( *eon )
	usage(EX_USAGE);
      break;
    case 'V':
      printf("flock (%s)\n", PACKAGE_STRING);
      exit(0);
    default:
      /* optopt will be set if this was an unrecognized option, i.e. *not* 'h' or '?' */
      usage(optopt ? EX_USAGE : 0);
      break;
    }
  }

  if ( argc > optind+1 ) {
    /* Run command */

    if ( !strcmp(argv[optind+1], "-c") ||
	 !strcmp(argv[optind+1], "--command") ) {

      if ( argc != optind+3 ) {
	fprintf(stderr, _("%s: %s requires exactly one command argument\n"),
		program, argv[optind+1]);
	exit(EX_USAGE);
      }

      cmd_argv = sh_c_argv;

      cmd_argv[0] = getenv("SHELL");
      if ( !cmd_argv[0] || !*cmd_argv[0] )
	cmd_argv[0] = _PATH_BSHELL;

      cmd_argv[1] = "-c";
      cmd_argv[2] = argv[optind+2];
      cmd_argv[3] = 0;
    } else {
      cmd_argv = &argv[optind+1];
    }

    filename = argv[optind];
    fd = open(filename, O_RDONLY|O_NOCTTY|O_CREAT, 0666);
    /* Linux doesn't like O_CREAT on a directory, even though it should be a
       no-op */
    if (fd < 0 && errno == EISDIR)
        fd = open(filename, O_RDONLY|O_NOCTTY);

    if ( fd < 0 ) {
      err = errno;
      fprintf(stderr, _("%s: cannot open lock file %s: %s\n"),
	      program, argv[optind], strerror(err));
      exit((err == ENOMEM||err == EMFILE||err == ENFILE) ? EX_OSERR :
	   (err == EROFS||err == ENOSPC) ? EX_CANTCREAT :
	   EX_NOINPUT);
    }

  } else if (optind < argc) {
    /* Use provided file descriptor */

    fd = (int)strtol(argv[optind], &eon, 10);
    if ( *eon || !argv[optind] ) {
      fprintf(stderr, _("%s: bad number: %s\n"), program, argv[optind]);
      exit(EX_USAGE);
    }

  } else {
    /* Bad options */

    fprintf(stderr, _("%s: requires file descriptor, file or directory\n"),
		program);
    exit(EX_USAGE);
  }


  if ( have_timeout ) {
    if ( timeout.it_value.tv_sec == 0 &&
	 timeout.it_value.tv_usec == 0 ) {
      /* -w 0 is equivalent to -n; this has to be special-cased
	 because setting an itimer to zero means disabled! */

      have_timeout = 0;
      block = LOCK_NB;
    } else {
      memset(&sa, 0, sizeof sa);

      sa.sa_handler = timeout_handler;
      sa.sa_flags   = SA_RESETHAND;
      sigaction(SIGALRM, &sa, &old_sa);

      setitimer(ITIMER_REAL, &timeout, &old_timer);
    }
  }

  while ( flock(fd, type|block) ) {
    switch( (err = errno) ) {
    case EWOULDBLOCK:		/* -n option set and failed to lock */
      exit(1);
    case EINTR:			/* Signal received */
      if ( timeout_expired )
	exit(1);		/* -w option set and failed to lock */
      continue;			/* otherwise try again */
    case EBADF:			/* since Linux 3.4 (commit 55725513) */
      /* Probably NFSv4 where flock() is emulated by fcntl().
       * Let's try to reopen in read-write mode.
       */
      if (!(open_flags & O_RDWR) &&
          type != LOCK_SH &&
          filename &&
          access(filename, R_OK | W_OK) == 0) {

              close(fd);
              open_flags = O_RDWR;
              fd = open(filename, open_flags);
              break;
      }
      /* go through */
    default:			/* Other errors */
      if ( filename )
	fprintf(stderr, "%s: %s: %s\n", program, filename, strerror(err));
      else
	fprintf(stderr, "%s: %d: %s\n", program, fd, strerror(err));
      exit((err == ENOLCK||err == ENOMEM) ? EX_OSERR : EX_DATAERR);
    }
  }

  if ( have_timeout ) {
    setitimer(ITIMER_REAL, &old_timer, NULL); /* Cancel itimer */
    sigaction(SIGALRM, &old_sa, NULL); /* Cancel signal handler */
  }

  status = 0;

  if ( cmd_argv ) {
    pid_t w, f;

    /* Clear any inherited settings */
    signal(SIGCHLD, SIG_DFL);
    f = fork();

    if ( f < 0 ) {
      err = errno;
      fprintf(stderr, _("%s: fork failed: %s\n"), program, strerror(err));
      exit(EX_OSERR);
    } else if ( f == 0 ) {
      if ( do_close )
	close(fd);
      err = errno;
      execvp(cmd_argv[0], cmd_argv);
      /* execvp() failed */
      fprintf(stderr, "%s: %s: %s\n", program, cmd_argv[0], strerror(err));
      _exit((err == ENOMEM) ? EX_OSERR: EX_UNAVAILABLE);
    } else {
      do {
	w = waitpid(f, &status, 0);
	if (w == -1 && errno != EINTR)
	  break;
      } while ( w != f );

      if (w == -1) {
	err = errno;
	status = EXIT_FAILURE;
	fprintf(stderr, "%s: waitpid failed: %s\n", program, strerror(err));
      } else if ( WIFEXITED(status) )
	status = WEXITSTATUS(status);
      else if ( WIFSIGNALED(status) )
	status = WTERMSIG(status) + 128;
      else
	status = EX_OSERR;	/* WTF? */
    }
  }

  return status;
}