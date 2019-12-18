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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  TS_VERIFY_CTX ;
typedef  int /*<<< orphan*/  TS_RESP ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_free (int /*<<< orphan*/ *) ; 
 int TS_RESP_verify_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TS_RESP_verify_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_VERIFY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * create_verify_ctx (char const*,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PKCS7_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_TS_RESP_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int verify_command(const char *data, const char *digest, const char *queryfile,
                          const char *in, int token_in,
                          const char *CApath, const char *CAfile,
                          const char *CAstore, const char *untrusted,
                          X509_VERIFY_PARAM *vpm)
{
    BIO *in_bio = NULL;
    PKCS7 *token = NULL;
    TS_RESP *response = NULL;
    TS_VERIFY_CTX *verify_ctx = NULL;
    int ret = 0;

    if ((in_bio = BIO_new_file(in, "rb")) == NULL)
        goto end;
    if (token_in) {
        if ((token = d2i_PKCS7_bio(in_bio, NULL)) == NULL)
            goto end;
    } else {
        if ((response = d2i_TS_RESP_bio(in_bio, NULL)) == NULL)
            goto end;
    }

    if ((verify_ctx = create_verify_ctx(data, digest, queryfile,
                                        CApath, CAfile, CAstore, untrusted,
                                        vpm)) == NULL)
        goto end;

    ret = token_in
        ? TS_RESP_verify_token(verify_ctx, token)
        : TS_RESP_verify_response(verify_ctx, response);

 end:
    printf("Verification: ");
    if (ret)
        printf("OK\n");
    else {
        printf("FAILED\n");
        ERR_print_errors(bio_err);
    }

    BIO_free_all(in_bio);
    PKCS7_free(token);
    TS_RESP_free(response);
    TS_VERIFY_CTX_free(verify_ctx);
    return ret;
}