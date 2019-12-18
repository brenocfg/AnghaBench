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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;

/* Variables and functions */
 char* X509_NAME_oneline (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
#define  X509_V_ERR_CERT_HAS_EXPIRED 130 
#define  X509_V_ERR_CERT_NOT_YET_VALID 129 
#define  X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT 128 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ ) ; 
 char* X509_verify_cert_error_string (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int verify_callback(int ok, X509_STORE_CTX *ctx)
{
    char *s, buf[256];

    s = X509_NAME_oneline(X509_get_subject_name(X509_STORE_CTX_get_current_cert(ctx)),
                          buf, sizeof(buf));
    if (s != NULL) {
        if (ok)
            printf("depth=%d %s\n", X509_STORE_CTX_get_error_depth(ctx), buf);
        else {
            fprintf(stderr, "depth=%d error=%d %s\n",
                    X509_STORE_CTX_get_error_depth(ctx),
                    X509_STORE_CTX_get_error(ctx), buf);
        }
    }

    if (ok == 0) {
        int i = X509_STORE_CTX_get_error(ctx);

        switch (i) {
        default:
            fprintf(stderr, "Error string: %s\n",
                    X509_verify_cert_error_string(i));
            break;
        case X509_V_ERR_CERT_NOT_YET_VALID:
        case X509_V_ERR_CERT_HAS_EXPIRED:
        case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            ok = 1;
            break;
        }
    }

    return ok;
}