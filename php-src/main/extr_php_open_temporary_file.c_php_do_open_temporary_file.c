#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  char wchar_t ;
struct TYPE_3__ {char* cwd; size_t cwd_length; } ;
typedef  TYPE_1__ cwd_state ;

/* Variables and functions */
 int /*<<< orphan*/  CWD_REALPATH ; 
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 scalar_t__ GetTempFileNameW (char*,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IS_SLASH (char) ; 
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  PHP_WIN32_CP_IGNORE_LEN ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ VCWD_CHMOD (char*,int) ; 
 int /*<<< orphan*/  VCWD_GETCWD (char*,int) ; 
 int VCWD_OPEN (char*,int) ; 
 int VCWD_OPEN_MODE (char*,int,int) ; 
 int _O_BINARY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int mkstemp (char*) ; 
 scalar_t__ mktemp (char*) ; 
 int /*<<< orphan*/  php_win32_check_trailing_space (char const*,size_t) ; 
 char* php_win32_ioutil_any_to_w (char const*) ; 
 char* php_win32_ioutil_conv_w_to_any (char*,int /*<<< orphan*/ ,size_t*) ; 
 int snprintf (char*,int,char*,char*,char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ virtual_file_ex (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_init (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_do_open_temporary_file(const char *path, const char *pfx, zend_string **opened_path_p)
{
#ifdef PHP_WIN32
	char *opened_path = NULL;
	size_t opened_path_len;
	wchar_t *cwdw, *pfxw, pathw[MAXPATHLEN];
#else
	char opened_path[MAXPATHLEN];
	char *trailing_slash;
#endif
	char cwd[MAXPATHLEN];
	cwd_state new_state;
	int fd = -1;
#ifndef HAVE_MKSTEMP
	int open_flags = O_CREAT | O_TRUNC | O_RDWR
#ifdef PHP_WIN32
		| _O_BINARY
#endif
		;
#endif

	if (!path || !path[0]) {
		return -1;
	}

#ifdef PHP_WIN32
	if (!php_win32_check_trailing_space(pfx, strlen(pfx))) {
		SetLastError(ERROR_INVALID_NAME);
		return -1;
	}
#endif

	if (!VCWD_GETCWD(cwd, MAXPATHLEN)) {
		cwd[0] = '\0';
	}

	new_state.cwd = estrdup(cwd);
	new_state.cwd_length = strlen(cwd);

	if (virtual_file_ex(&new_state, path, NULL, CWD_REALPATH)) {
		efree(new_state.cwd);
		return -1;
	}

#ifndef PHP_WIN32
	if (IS_SLASH(new_state.cwd[new_state.cwd_length - 1])) {
		trailing_slash = "";
	} else {
		trailing_slash = "/";
	}

	if (snprintf(opened_path, MAXPATHLEN, "%s%s%sXXXXXX", new_state.cwd, trailing_slash, pfx) >= MAXPATHLEN) {
		efree(new_state.cwd);
		return -1;
	}
#endif

#ifdef PHP_WIN32
	cwdw = php_win32_ioutil_any_to_w(new_state.cwd);
	pfxw = php_win32_ioutil_any_to_w(pfx);
	if (!cwdw || !pfxw) {
		free(cwdw);
		free(pfxw);
		efree(new_state.cwd);
		return -1;
	}

	if (GetTempFileNameW(cwdw, pfxw, 0, pathw)) {
		opened_path = php_win32_ioutil_conv_w_to_any(pathw, PHP_WIN32_CP_IGNORE_LEN, &opened_path_len);
		if (!opened_path || opened_path_len >= MAXPATHLEN) {
			free(cwdw);
			free(pfxw);
			efree(new_state.cwd);
			return -1;
		}
		assert(strlen(opened_path) == opened_path_len);

		/* Some versions of windows set the temp file to be read-only,
		 * which means that opening it will fail... */
		if (VCWD_CHMOD(opened_path, 0600)) {
			free(cwdw);
			free(pfxw);
			efree(new_state.cwd);
			free(opened_path);
			return -1;
		}
		fd = VCWD_OPEN_MODE(opened_path, open_flags, 0600);
	}

	free(cwdw);
	free(pfxw);
#elif defined(HAVE_MKSTEMP)
	fd = mkstemp(opened_path);
#else
	if (mktemp(opened_path)) {
		fd = VCWD_OPEN(opened_path, open_flags);
	}
#endif

#ifdef PHP_WIN32
	if (fd != -1 && opened_path_p) {
		*opened_path_p = zend_string_init(opened_path, opened_path_len, 0);
	}
	free(opened_path);
#else
	if (fd != -1 && opened_path_p) {
		*opened_path_p = zend_string_init(opened_path, strlen(opened_path), 0);
	}
#endif
	efree(new_state.cwd);
	return fd;
}