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
typedef  int /*<<< orphan*/  TS_REQ ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_ASN1 ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 int /*<<< orphan*/  TS_REQ_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_REQ_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char const*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_query (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,char const*,int,int) ; 
 int /*<<< orphan*/ * d2i_TS_REQ_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_TS_REQ_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_command(const char *data, const char *digest, const EVP_MD *md,
                         const char *policy, int no_nonce,
                         int cert, const char *in, const char *out, int text)
{
    int ret = 0;
    TS_REQ *query = NULL;
    BIO *in_bio = NULL;
    BIO *data_bio = NULL;
    BIO *out_bio = NULL;

    /* Build query object. */
    if (in != NULL) {
        if ((in_bio = bio_open_default(in, 'r', FORMAT_ASN1)) == NULL)
            goto end;
        query = d2i_TS_REQ_bio(in_bio, NULL);
    } else {
        if (digest == NULL
            && (data_bio = bio_open_default(data, 'r', FORMAT_ASN1)) == NULL)
            goto end;
        query = create_query(data_bio, digest, md, policy, no_nonce, cert);
    }
    if (query == NULL)
        goto end;

    if (text) {
        if ((out_bio = bio_open_default(out, 'w', FORMAT_TEXT)) == NULL)
            goto end;
        if (!TS_REQ_print_bio(out_bio, query))
            goto end;
    } else {
        if ((out_bio = bio_open_default(out, 'w', FORMAT_ASN1)) == NULL)
            goto end;
        if (!i2d_TS_REQ_bio(out_bio, query))
            goto end;
    }

    ret = 1;

 end:
    ERR_print_errors(bio_err);
    BIO_free_all(in_bio);
    BIO_free_all(data_bio);
    BIO_free_all(out_bio);
    TS_REQ_free(query);
    return ret;
}