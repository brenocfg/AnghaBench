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
struct app_verify_arg {char* string; scalar_t__ app_verify; } ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 char* X509_NAME_oneline (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get0_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int X509_verify_cert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int app_verify_callback(X509_STORE_CTX *ctx, void *arg)
{
    int ok = 1;
    struct app_verify_arg *cb_arg = arg;

    if (cb_arg->app_verify) {
        char *s = NULL, buf[256];
        X509 *c = X509_STORE_CTX_get0_cert(ctx);

        printf("In app_verify_callback, allowing cert. ");
        printf("Arg is: %s\n", cb_arg->string);
        printf("Finished printing do we have a context? 0x%p a cert? 0x%p\n",
                (void *)ctx, (void *)c);
        if (c)
            s = X509_NAME_oneline(X509_get_subject_name(c), buf, 256);
        if (s != NULL) {
            printf("cert depth=%d %s\n",
                    X509_STORE_CTX_get_error_depth(ctx), buf);
        }
        return 1;
    }

    ok = X509_verify_cert(ctx);

    return ok;
}