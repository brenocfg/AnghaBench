#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * handshake_buffer; int /*<<< orphan*/ * handshake_dgst; } ;
struct TYPE_7__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 long BIO_get_mem_data (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void*,long) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_DIGEST_CACHED_RECORDS ; 
 int /*<<< orphan*/  SSL_R_BAD_HANDSHAKE_LENGTH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_2__*) ; 

int ssl3_digest_cached_records(SSL *s, int keep)
{
    const EVP_MD *md;
    long hdatalen;
    void *hdata;

    if (s->s3.handshake_dgst == NULL) {
        hdatalen = BIO_get_mem_data(s->s3.handshake_buffer, &hdata);
        if (hdatalen <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_DIGEST_CACHED_RECORDS,
                     SSL_R_BAD_HANDSHAKE_LENGTH);
            return 0;
        }

        s->s3.handshake_dgst = EVP_MD_CTX_new();
        if (s->s3.handshake_dgst == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_DIGEST_CACHED_RECORDS,
                     ERR_R_MALLOC_FAILURE);
            return 0;
        }

        md = ssl_handshake_md(s);
        if (md == NULL || !EVP_DigestInit_ex(s->s3.handshake_dgst, md, NULL)
            || !EVP_DigestUpdate(s->s3.handshake_dgst, hdata, hdatalen)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_DIGEST_CACHED_RECORDS,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
    if (keep == 0) {
        BIO_free(s->s3.handshake_buffer);
        s->s3.handshake_buffer = NULL;
    }

    return 1;
}