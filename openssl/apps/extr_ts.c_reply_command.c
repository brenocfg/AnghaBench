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
typedef  int /*<<< orphan*/  TS_TST_INFO ;
typedef  int /*<<< orphan*/  TS_RESP ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_ASN1 ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 int /*<<< orphan*/  TS_RESP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_RESP_get_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TS_RESP_get_tst_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_RESP_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_TST_INFO_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_response (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/  const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/ * d2i_TS_RESP_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_PKCS7_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_TS_RESP_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_PKCS7 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reply_command(CONF *conf, const char *section, const char *engine,
                         const char *queryfile, const char *passin, const char *inkey,
                         const EVP_MD *md, const char *signer, const char *chain,
                         const char *policy, const char *in, int token_in,
                         const char *out, int token_out, int text)
{
    int ret = 0;
    TS_RESP *response = NULL;
    BIO *in_bio = NULL;
    BIO *query_bio = NULL;
    BIO *inkey_bio = NULL;
    BIO *signer_bio = NULL;
    BIO *out_bio = NULL;

    if (in != NULL) {
        if ((in_bio = BIO_new_file(in, "rb")) == NULL)
            goto end;
        if (token_in) {
            response = read_PKCS7(in_bio);
        } else {
            response = d2i_TS_RESP_bio(in_bio, NULL);
        }
    } else {
        response = create_response(conf, section, engine, queryfile,
                                   passin, inkey, md, signer, chain, policy);
        if (response != NULL)
            BIO_printf(bio_err, "Response has been generated.\n");
        else
            BIO_printf(bio_err, "Response is not generated.\n");
    }
    if (response == NULL)
        goto end;

    /* Write response. */
    if (text) {
        if ((out_bio = bio_open_default(out, 'w', FORMAT_TEXT)) == NULL)
        goto end;
        if (token_out) {
            TS_TST_INFO *tst_info = TS_RESP_get_tst_info(response);
            if (!TS_TST_INFO_print_bio(out_bio, tst_info))
                goto end;
        } else {
            if (!TS_RESP_print_bio(out_bio, response))
                goto end;
        }
    } else {
        if ((out_bio = bio_open_default(out, 'w', FORMAT_ASN1)) == NULL)
            goto end;
        if (token_out) {
            PKCS7 *token = TS_RESP_get_token(response);
            if (!i2d_PKCS7_bio(out_bio, token))
                goto end;
        } else {
            if (!i2d_TS_RESP_bio(out_bio, response))
                goto end;
        }
    }

    ret = 1;

 end:
    ERR_print_errors(bio_err);
    BIO_free_all(in_bio);
    BIO_free_all(query_bio);
    BIO_free_all(inkey_bio);
    BIO_free_all(signer_bio);
    BIO_free_all(out_bio);
    TS_RESP_free(response);
    return ret;
}