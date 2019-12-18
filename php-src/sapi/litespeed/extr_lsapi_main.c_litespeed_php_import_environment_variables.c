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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 size_t TRACK_VARS_ENV ; 
 size_t TRACK_VARS_SERVER ; 
 int /*<<< orphan*/  ZVAL_DUP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_ARR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ARR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_variable (char*,unsigned long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char** environ ; 
 char* erealloc (char*,size_t) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned long) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  tsrm_env_lock () ; 
 int /*<<< orphan*/  tsrm_env_unlock () ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void litespeed_php_import_environment_variables(zval *array_ptr)
{
    char buf[128];
    char **env, *p, *t = buf;
    size_t alloc_size = sizeof(buf);
    unsigned long nlen; /* ptrdiff_t is not portable */

    if (Z_TYPE(PG(http_globals)[TRACK_VARS_ENV]) == IS_ARRAY &&
        Z_ARR_P(array_ptr) != Z_ARR(PG(http_globals)[TRACK_VARS_ENV]) &&
        zend_hash_num_elements(Z_ARRVAL(PG(http_globals)[TRACK_VARS_ENV])) > 0
    ) {
        zval_ptr_dtor_nogc(array_ptr);
        ZVAL_DUP(array_ptr, &PG(http_globals)[TRACK_VARS_ENV]);
        return;
    } else if (Z_TYPE(PG(http_globals)[TRACK_VARS_SERVER]) == IS_ARRAY &&
        Z_ARR_P(array_ptr) != Z_ARR(PG(http_globals)[TRACK_VARS_SERVER]) &&
        zend_hash_num_elements(Z_ARRVAL(PG(http_globals)[TRACK_VARS_SERVER])) > 0
    ) {
        zval_ptr_dtor_nogc(array_ptr);
        ZVAL_DUP(array_ptr, &PG(http_globals)[TRACK_VARS_SERVER]);
        return;
    }

    tsrm_env_lock();
    for (env = environ; env != NULL && *env != NULL; env++) {
        p = strchr(*env, '=');
        if (!p) {               /* malformed entry? */
            continue;
        }
        nlen = p - *env;
        if (nlen >= alloc_size) {
            alloc_size = nlen + 64;
            t = (t == buf ? emalloc(alloc_size): erealloc(t, alloc_size));
        }
        memcpy(t, *env, nlen);
        t[nlen] = '\0';
        add_variable(t, nlen, p + 1, strlen( p + 1 ), array_ptr);
    }
    tsrm_env_unlock();
    if (t != buf && t != NULL) {
        efree(t);
    }
}