#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {scalar_t__ fd; int /*<<< orphan*/  filemode; int /*<<< orphan*/ * lastkey; } ;
typedef  TYPE_1__ ps_files ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  LOCK_EX ; 
 int MAXPATHLEN ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ PG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ VCWD_OPEN_MODE (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * estrdup (char const*) ; 
 int flock (int,int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  open_basedir ; 
 scalar_t__ php_check_open_basedir (char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ php_session_valid_key (char const*) ; 
 int /*<<< orphan*/  ps_files_close (TYPE_1__*) ; 
 int /*<<< orphan*/  ps_files_path_create (char*,int,TYPE_1__*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ zend_fstat (int,struct stat*) ; 

__attribute__((used)) static void ps_files_open(ps_files *data, const char *key)
{
	char buf[MAXPATHLEN];
#if !defined(O_NOFOLLOW) || !defined(PHP_WIN32)
    struct stat sbuf;
#endif
	int ret;

	if (data->fd < 0 || !data->lastkey || strcmp(key, data->lastkey)) {
		if (data->lastkey) {
			efree(data->lastkey);
			data->lastkey = NULL;
		}

		ps_files_close(data);

		if (php_session_valid_key(key) == FAILURE) {
			php_error_docref(NULL, E_WARNING, "The session id is too long or contains illegal characters, valid characters are a-z, A-Z, 0-9 and '-,'");
			return;
		}

		if (!ps_files_path_create(buf, sizeof(buf), data, key)) {
			php_error_docref(NULL, E_WARNING, "Failed to create session data file path. Too short session ID, invalid save_path or path lentgth exceeds MAXPATHLEN(%d)", MAXPATHLEN);
			return;
		}

		data->lastkey = estrdup(key);

		/* O_NOFOLLOW to prevent us from following evil symlinks */
#ifdef O_NOFOLLOW
		data->fd = VCWD_OPEN_MODE(buf, O_CREAT | O_RDWR | O_BINARY | O_NOFOLLOW, data->filemode);
#else
		/* Check to make sure that the opened file is not outside of allowable dirs.
		   This is not 100% safe but it's hard to do something better without O_NOFOLLOW */
		if(PG(open_basedir) && lstat(buf, &sbuf) == 0 && S_ISLNK(sbuf.st_mode) && php_check_open_basedir(buf)) {
			return;
		}
		data->fd = VCWD_OPEN_MODE(buf, O_CREAT | O_RDWR | O_BINARY, data->filemode);
#endif

		if (data->fd != -1) {
#ifndef PHP_WIN32
			/* check that this session file was created by us or root – we
			   don't want to end up accepting the sessions of another webapp

			   If the process is ran by root, we ignore session file ownership
			   Use case: session is initiated by Apache under non-root and then
			   accessed by backend with root permissions to execute some system tasks.

			   */
			if (zend_fstat(data->fd, &sbuf) || (sbuf.st_uid != 0 && sbuf.st_uid != getuid() && sbuf.st_uid != geteuid() && getuid() != 0)) {
				close(data->fd);
				data->fd = -1;
				php_error_docref(NULL, E_WARNING, "Session data file is not created by your uid");
				return;
			}
#endif
			do {
				ret = flock(data->fd, LOCK_EX);
			} while (ret == -1 && errno == EINTR);

#ifdef F_SETFD
# ifndef FD_CLOEXEC
#  define FD_CLOEXEC 1
# endif
			if (fcntl(data->fd, F_SETFD, FD_CLOEXEC)) {
				php_error_docref(NULL, E_WARNING, "fcntl(%d, F_SETFD, FD_CLOEXEC) failed: %s (%d)", data->fd, strerror(errno), errno);
			}
#endif
		} else {
			php_error_docref(NULL, E_WARNING, "open(%s, O_RDWR) failed: %s (%d)", buf, strerror(errno), errno);
		}
	}
}