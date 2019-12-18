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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_verify_cert_error_string (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  print_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int callb(int ok, X509_STORE_CTX *ctx)
{
    int err;
    X509 *err_cert;

    /*
     * it is ok to use a self signed certificate This case will catch both
     * the initial ok == 0 and the final ok == 1 calls to this function
     */
    err = X509_STORE_CTX_get_error(ctx);
    if (err == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
        return 1;

    /*
     * BAD we should have gotten an error.  Normally if everything worked
     * X509_STORE_CTX_get_error(ctx) will still be set to
     * DEPTH_ZERO_SELF_....
     */
    if (ok) {
        BIO_printf(bio_err,
                   "error with certificate to be certified - should be self signed\n");
        return 0;
    } else {
        err_cert = X509_STORE_CTX_get_current_cert(ctx);
        print_name(bio_err, NULL, X509_get_subject_name(err_cert), 0);
        BIO_printf(bio_err,
                   "error with certificate - error %d at depth %d\n%s\n", err,
                   X509_STORE_CTX_get_error_depth(ctx),
                   X509_verify_cert_error_string(err));
        return 1;
    }
}