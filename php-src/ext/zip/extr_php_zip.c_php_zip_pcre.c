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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pcre2_match_data ;
typedef  int /*<<< orphan*/  pcre2_match_context ;
typedef  int /*<<< orphan*/  pcre2_code ;
typedef  int /*<<< orphan*/  PCRE2_SPTR ;

/* Variables and functions */
 char* DEFAULT_SLASH ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*,int) ; 
 scalar_t__ IS_SLASH (char) ; 
 int MAXPATHLEN ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 char* VCWD_GETCWD (char*,int) ; 
 scalar_t__ VCWD_STAT (char*,TYPE_1__*) ; 
 scalar_t__ ZIP_OPENBASEDIR_CHECKPATH (char*) ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ **) ; 
 int pcre2_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcre_get_compiled_regex (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * php_pcre_create_match_data (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_pcre_free_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_pcre_mctx () ; 
 scalar_t__ php_stream_dirent_alphasort ; 
 int php_stream_scandir (char*,int /*<<< orphan*/ ***,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int php_zip_pcre(zend_string *regexp, char *path, int path_len, zval *return_value) /* {{{ */
{
#ifdef ZTS
	char cwd[MAXPATHLEN];
	char work_path[MAXPATHLEN];
	char *result;
#endif
	int files_cnt;
	zend_string **namelist;
	pcre2_match_context *mctx = php_pcre_mctx();

#ifdef ZTS
	if (!IS_ABSOLUTE_PATH(path, path_len)) {
		result = VCWD_GETCWD(cwd, MAXPATHLEN);
		if (!result) {
			cwd[0] = '\0';
		}
#ifdef PHP_WIN32
		if (IS_SLASH(*path)) {
			cwd[2] = '\0';
		}
#endif
		snprintf(work_path, MAXPATHLEN, "%s%c%s", cwd, DEFAULT_SLASH, path);
		path = work_path;
	}
#endif

	if (ZIP_OPENBASEDIR_CHECKPATH(path)) {
		return -1;
	}

	files_cnt = php_stream_scandir(path, &namelist, NULL, (void *) php_stream_dirent_alphasort);

	if (files_cnt > 0) {
		pcre2_code *re = NULL;
		pcre2_match_data *match_data = NULL;
		uint32_t i, capture_count;
		int rc;

		re = pcre_get_compiled_regex(regexp, &capture_count);
		if (!re) {
			php_error_docref(NULL, E_WARNING, "Invalid expression");
			return -1;
		}

		array_init(return_value);

		/* only the files, directories are ignored */
		for (i = 0; i < files_cnt; i++) {
			zend_stat_t s;
			char   fullpath[MAXPATHLEN];
			size_t    namelist_len = ZSTR_LEN(namelist[i]);

			if ((namelist_len == 1 && ZSTR_VAL(namelist[i])[0] == '.') ||
				(namelist_len == 2 && ZSTR_VAL(namelist[i])[0] == '.' && ZSTR_VAL(namelist[i])[1] == '.')) {
				zend_string_release_ex(namelist[i], 0);
				continue;
			}

			if ((path_len + namelist_len + 1) >= MAXPATHLEN) {
				php_error_docref(NULL, E_WARNING, "add_path string too long (max: %u, %zu given)",
						MAXPATHLEN - 1, (path_len + namelist_len + 1));
				zend_string_release_ex(namelist[i], 0);
				break;
			}

			match_data = php_pcre_create_match_data(capture_count, re);
			if (!match_data) {
				/* Allocation failed, but can proceed to the next pattern. */
				zend_string_release_ex(namelist[i], 0);
				continue;
			}
			rc = pcre2_match(re, (PCRE2_SPTR)ZSTR_VAL(namelist[i]), ZSTR_LEN(namelist[i]), 0, 0, match_data, mctx);
			php_pcre_free_match_data(match_data);
			/* 0 means that the vector is too small to hold all the captured substring offsets */
			if (rc < 0) {
				zend_string_release_ex(namelist[i], 0);
				continue;
			}

			snprintf(fullpath, MAXPATHLEN, "%s%c%s", path, DEFAULT_SLASH, ZSTR_VAL(namelist[i]));

			if (0 != VCWD_STAT(fullpath, &s)) {
				php_error_docref(NULL, E_WARNING, "Cannot read <%s>", fullpath);
				zend_string_release_ex(namelist[i], 0);
				continue;
			}

			if (S_IFDIR == (s.st_mode & S_IFMT)) {
				zend_string_release_ex(namelist[i], 0);
				continue;
			}

			add_next_index_string(return_value, fullpath);
			zend_string_release_ex(namelist[i], 0);
		}
		efree(namelist);
	}
	return files_cnt;
}