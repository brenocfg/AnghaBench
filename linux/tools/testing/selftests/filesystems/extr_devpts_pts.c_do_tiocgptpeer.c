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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int KSFT_SKIP ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_RDWR ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGPTPEER ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ioctl (int,int /*<<< orphan*/ ,int) ; 
 int login_pty (int) ; 
 int open (char*,int) ; 
 int resolve_procfd_symlink (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int unlockpt (int) ; 
 int wait_for_pid (scalar_t__) ; 

__attribute__((used)) static int do_tiocgptpeer(char *ptmx, char *expected_procfd_contents)
{
	int ret;
	int master = -1, slave = -1, fret = -1;

	master = open(ptmx, O_RDWR | O_NOCTTY | O_CLOEXEC);
	if (master < 0) {
		fprintf(stderr, "Failed to open \"%s\": %s\n", ptmx,
			strerror(errno));
		return -1;
	}

	/*
	 * grantpt() makes assumptions about /dev/pts/ so ignore it. It's also
	 * not really needed.
	 */
	ret = unlockpt(master);
	if (ret < 0) {
		fprintf(stderr, "Failed to unlock terminal\n");
		goto do_cleanup;
	}

#ifdef TIOCGPTPEER
	slave = ioctl(master, TIOCGPTPEER, O_RDWR | O_NOCTTY | O_CLOEXEC);
#endif
	if (slave < 0) {
		if (errno == EINVAL) {
			fprintf(stderr, "TIOCGPTPEER is not supported. "
					"Skipping test.\n");
			fret = KSFT_SKIP;
		} else {
			fprintf(stderr,
				"Failed to perform TIOCGPTPEER ioctl\n");
			fret = EXIT_FAILURE;
		}
		goto do_cleanup;
	}

	pid_t pid = fork();
	if (pid < 0)
		goto do_cleanup;

	if (pid == 0) {
		char buf[4096];

		ret = login_pty(slave);
		if (ret < 0) {
			fprintf(stderr, "Failed to setup terminal\n");
			_exit(EXIT_FAILURE);
		}

		ret = resolve_procfd_symlink(STDIN_FILENO, buf, sizeof(buf));
		if (ret < 0) {
			fprintf(stderr, "Failed to retrieve pathname of pts "
					"slave file descriptor\n");
			_exit(EXIT_FAILURE);
		}

		if (strncmp(expected_procfd_contents, buf,
			    strlen(expected_procfd_contents)) != 0) {
			fprintf(stderr, "Received invalid contents for "
					"\"/proc/<pid>/fd/%d\" symlink: %s\n",
					STDIN_FILENO, buf);
			_exit(-1);
		}

		fprintf(stderr, "Contents of \"/proc/<pid>/fd/%d\" "
				"symlink are valid: %s\n", STDIN_FILENO, buf);

		_exit(EXIT_SUCCESS);
	}

	ret = wait_for_pid(pid);
	if (ret < 0)
		goto do_cleanup;

	fret = EXIT_SUCCESS;

do_cleanup:
	if (master >= 0)
		close(master);
	if (slave >= 0)
		close(slave);

	return fret;
}