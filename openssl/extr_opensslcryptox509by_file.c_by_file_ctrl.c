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
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 long X509_FILETYPE_DEFAULT ; 
 long X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_F_BY_FILE_CTRL ; 
#define  X509_L_FILE_LOAD 128 
 int /*<<< orphan*/  X509_R_LOADING_DEFAULTS ; 
 char const* X509_get_default_cert_file () ; 
 int /*<<< orphan*/  X509_get_default_cert_file_env () ; 
 int /*<<< orphan*/  X509_load_cert_crl_file (int /*<<< orphan*/ *,char const*,long) ; 
 int /*<<< orphan*/  X509_load_cert_file (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ossl_safe_getenv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int by_file_ctrl(X509_LOOKUP *ctx, int cmd, const char *argp,
                        long argl, char **ret)
{
    int ok = 0;
    const char *file;

    switch (cmd) {
    case X509_L_FILE_LOAD:
        if (argl == X509_FILETYPE_DEFAULT) {
            file = ossl_safe_getenv(X509_get_default_cert_file_env());
            if (file)
                ok = (X509_load_cert_crl_file(ctx, file,
                                              X509_FILETYPE_PEM) != 0);

            else
                ok = (X509_load_cert_crl_file
                      (ctx, X509_get_default_cert_file(),
                       X509_FILETYPE_PEM) != 0);

            if (!ok) {
                X509err(X509_F_BY_FILE_CTRL, X509_R_LOADING_DEFAULTS);
            }
        } else {
            if (argl == X509_FILETYPE_PEM)
                ok = (X509_load_cert_crl_file(ctx, argp,
                                              X509_FILETYPE_PEM) != 0);
            else
                ok = (X509_load_cert_file(ctx, argp, (int)argl) != 0);
        }
        break;
    }
    return ok;
}