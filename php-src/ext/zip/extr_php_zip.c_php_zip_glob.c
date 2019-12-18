#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  int zend_long ;
struct TYPE_7__ {size_t gl_pathc; scalar_t__* gl_pathv; scalar_t__ gl_offs; } ;
typedef  TYPE_2__ glob_t ;

/* Variables and functions */
 char* DEFAULT_SLASH ; 
 int /*<<< orphan*/  E_WARNING ; 
 int GLOB_AVAILABLE_FLAGS ; 
 int GLOB_FLAGMASK ; 
 int GLOB_NOMATCH ; 
 int GLOB_ONLYDIR ; 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*,int) ; 
 scalar_t__ IS_SLASH (char) ; 
 int MAXPATHLEN ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 char* VCWD_GETCWD (char*,int) ; 
 scalar_t__ VCWD_STAT (scalar_t__,TYPE_1__*) ; 
 scalar_t__ ZIP_OPENBASEDIR_CHECKPATH (char*) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int glob (char*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  globfree (TYPE_2__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*) ; 

int php_zip_glob(char *pattern, int pattern_len, zend_long flags, zval *return_value) /* {{{ */
{
#ifdef HAVE_GLOB
	char cwd[MAXPATHLEN];
	int cwd_skip = 0;
#ifdef ZTS
	char work_pattern[MAXPATHLEN];
	char *result;
#endif
	glob_t globbuf;
	size_t n;
	int ret;

	if (pattern_len >= MAXPATHLEN) {
		php_error_docref(NULL, E_WARNING, "Pattern exceeds the maximum allowed length of %d characters", MAXPATHLEN);
		return -1;
	}

	if ((GLOB_AVAILABLE_FLAGS & flags) != flags) {
		php_error_docref(NULL, E_WARNING, "At least one of the passed flags is invalid or not supported on this platform");
		return -1;
	}

#ifdef ZTS
	if (!IS_ABSOLUTE_PATH(pattern, pattern_len)) {
		result = VCWD_GETCWD(cwd, MAXPATHLEN);
		if (!result) {
			cwd[0] = '\0';
		}
#ifdef PHP_WIN32
		if (IS_SLASH(*pattern)) {
			cwd[2] = '\0';
		}
#endif
		cwd_skip = strlen(cwd)+1;

		snprintf(work_pattern, MAXPATHLEN, "%s%c%s", cwd, DEFAULT_SLASH, pattern);
		pattern = work_pattern;
	}
#endif

	globbuf.gl_offs = 0;
	if (0 != (ret = glob(pattern, flags & GLOB_FLAGMASK, NULL, &globbuf))) {
#ifdef GLOB_NOMATCH
		if (GLOB_NOMATCH == ret) {
			/* Some glob implementation simply return no data if no matches
			   were found, others return the GLOB_NOMATCH error code.
			   We don't want to treat GLOB_NOMATCH as an error condition
			   so that PHP glob() behaves the same on both types of
			   implementations and so that 'foreach (glob() as ...'
			   can be used for simple glob() calls without further error
			   checking.
			*/
			array_init(return_value);
			return 0;
		}
#endif
		return 0;
	}

	/* now catch the FreeBSD style of "no matches" */
	if (!globbuf.gl_pathc || !globbuf.gl_pathv) {
		array_init(return_value);
		return 0;
	}

	/* we assume that any glob pattern will match files from one directory only
	   so checking the dirname of the first match should be sufficient */
	strncpy(cwd, globbuf.gl_pathv[0], MAXPATHLEN);
	if (ZIP_OPENBASEDIR_CHECKPATH(cwd)) {
		return -1;
	}

	array_init(return_value);
	for (n = 0; n < globbuf.gl_pathc; n++) {
		/* we need to do this every time since GLOB_ONLYDIR does not guarantee that
		 * all directories will be filtered. GNU libc documentation states the
		 * following:
		 * If the information about the type of the file is easily available
		 * non-directories will be rejected but no extra work will be done to
		 * determine the information for each file. I.e., the caller must still be
		 * able to filter directories out.
		 */
		if (flags & GLOB_ONLYDIR) {
			zend_stat_t s;

			if (0 != VCWD_STAT(globbuf.gl_pathv[n], &s)) {
				continue;
			}

			if (S_IFDIR != (s.st_mode & S_IFMT)) {
				continue;
			}
		}
		add_next_index_string(return_value, globbuf.gl_pathv[n]+cwd_skip);
	}

	globfree(&globbuf);
	return globbuf.gl_pathc;
#else
	zend_throw_error(NULL, "Glob support is not available");
	return 0;
#endif  /* HAVE_GLOB */
}