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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  component ;
typedef  scalar_t__ (* OSSL_cmp_log_cb_t ) (char*,char const*,int,int /*<<< orphan*/ ,char*) ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,char const*,...) ; 
 int ERR_TXT_STRING ; 
 unsigned long ERR_get_error_all (char const**,int*,char const**,char const**,int*) ; 
 int /*<<< orphan*/  ERR_lib_error_string (unsigned long) ; 
 int ERR_print_errors_cb_LIMIT ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_reason_error_string (unsigned long) ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_ERR ; 
 int /*<<< orphan*/  stderr ; 

void OSSL_CMP_print_errors_cb(OSSL_cmp_log_cb_t log_fn)
{
    unsigned long err;
    char msg[ERR_print_errors_cb_LIMIT];
    const char *file = NULL, *func = NULL, *data = NULL;
    int line, flags;

    if (log_fn == NULL) {
#ifndef OPENSSL_NO_STDIO
        ERR_print_errors_fp(stderr);
#else
        /* CMPerr(0, CMP_R_NO_STDIO) makes no sense during error printing */
#endif
        return;
    }

    while ((err = ERR_get_error_all(&file, &line, &func, &data, &flags)) != 0) {
        char component[128];
        const char *func_ = func != NULL && *func != '\0' ? func : "<unknown>";

        if (!(flags & ERR_TXT_STRING))
            data = NULL;
#ifdef OSSL_CMP_PRINT_LIBINFO
        BIO_snprintf(component, sizeof(component), "OpenSSL:%s:%s",
                     ERR_lib_error_string(err), func_);
#else
        BIO_snprintf(component, sizeof(component), "%s",func_);
#endif
        BIO_snprintf(msg, sizeof(msg), "%s%s%s", ERR_reason_error_string(err),
                     data == NULL ? "" : " : ", data == NULL ? "" : data);
        if (log_fn(component, file, line, OSSL_CMP_LOG_ERR, msg) <= 0)
            break;              /* abort outputting the error report */
    }
}