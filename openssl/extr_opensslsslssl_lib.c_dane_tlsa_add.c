#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_11__ {scalar_t__ usage; scalar_t__ selector; size_t mtype; size_t dlen; int /*<<< orphan*/ * spki; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ danetls_record ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_12__ {int umask; int /*<<< orphan*/ * trecs; TYPE_1__* dctx; int /*<<< orphan*/ * certs; } ;
struct TYPE_10__ {scalar_t__* mdord; } ;
typedef  TYPE_3__ SSL_DANE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ DANETLS_MATCHING_FULL ; 
#define  DANETLS_SELECTOR_CERT 129 
 scalar_t__ DANETLS_SELECTOR_LAST ; 
#define  DANETLS_SELECTOR_SPKI 128 
 int DANETLS_TA_MASK ; 
 int DANETLS_USAGE_BIT (scalar_t__) ; 
 scalar_t__ DANETLS_USAGE_DANE_TA ; 
 scalar_t__ DANETLS_USAGE_LAST ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (size_t) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_F_DANE_TLSA_ADD ; 
 int /*<<< orphan*/  SSL_R_DANE_NOT_ENABLED ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_CERTIFICATE ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_CERTIFICATE_USAGE ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_DATA_LENGTH ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_MATCHING_TYPE ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_PUBLIC_KEY ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_BAD_SELECTOR ; 
 int /*<<< orphan*/  SSL_R_DANE_TLSA_NULL_DATA ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d2i_PUBKEY (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int /*<<< orphan*/  d2i_X509 (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_danetls_record_insert (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int sk_danetls_record_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_danetls_record_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tlsa_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * tlsa_md_get (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int dane_tlsa_add(SSL_DANE *dane,
                         uint8_t usage,
                         uint8_t selector,
                         uint8_t mtype, unsigned const char *data, size_t dlen)
{
    danetls_record *t;
    const EVP_MD *md = NULL;
    int ilen = (int)dlen;
    int i;
    int num;

    if (dane->trecs == NULL) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_NOT_ENABLED);
        return -1;
    }

    if (ilen < 0 || dlen != (size_t)ilen) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_DATA_LENGTH);
        return 0;
    }

    if (usage > DANETLS_USAGE_LAST) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_CERTIFICATE_USAGE);
        return 0;
    }

    if (selector > DANETLS_SELECTOR_LAST) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_SELECTOR);
        return 0;
    }

    if (mtype != DANETLS_MATCHING_FULL) {
        md = tlsa_md_get(dane, mtype);
        if (md == NULL) {
            SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_MATCHING_TYPE);
            return 0;
        }
    }

    if (md != NULL && dlen != (size_t)EVP_MD_size(md)) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_DIGEST_LENGTH);
        return 0;
    }
    if (!data) {
        SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_NULL_DATA);
        return 0;
    }

    if ((t = OPENSSL_zalloc(sizeof(*t))) == NULL) {
        SSLerr(SSL_F_DANE_TLSA_ADD, ERR_R_MALLOC_FAILURE);
        return -1;
    }

    t->usage = usage;
    t->selector = selector;
    t->mtype = mtype;
    t->data = OPENSSL_malloc(dlen);
    if (t->data == NULL) {
        tlsa_free(t);
        SSLerr(SSL_F_DANE_TLSA_ADD, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    memcpy(t->data, data, dlen);
    t->dlen = dlen;

    /* Validate and cache full certificate or public key */
    if (mtype == DANETLS_MATCHING_FULL) {
        const unsigned char *p = data;
        X509 *cert = NULL;
        EVP_PKEY *pkey = NULL;

        switch (selector) {
        case DANETLS_SELECTOR_CERT:
            if (!d2i_X509(&cert, &p, ilen) || p < data ||
                dlen != (size_t)(p - data)) {
                tlsa_free(t);
                SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_CERTIFICATE);
                return 0;
            }
            if (X509_get0_pubkey(cert) == NULL) {
                tlsa_free(t);
                SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_CERTIFICATE);
                return 0;
            }

            if ((DANETLS_USAGE_BIT(usage) & DANETLS_TA_MASK) == 0) {
                X509_free(cert);
                break;
            }

            /*
             * For usage DANE-TA(2), we support authentication via "2 0 0" TLSA
             * records that contain full certificates of trust-anchors that are
             * not present in the wire chain.  For usage PKIX-TA(0), we augment
             * the chain with untrusted Full(0) certificates from DNS, in case
             * they are missing from the chain.
             */
            if ((dane->certs == NULL &&
                 (dane->certs = sk_X509_new_null()) == NULL) ||
                !sk_X509_push(dane->certs, cert)) {
                SSLerr(SSL_F_DANE_TLSA_ADD, ERR_R_MALLOC_FAILURE);
                X509_free(cert);
                tlsa_free(t);
                return -1;
            }
            break;

        case DANETLS_SELECTOR_SPKI:
            if (!d2i_PUBKEY(&pkey, &p, ilen) || p < data ||
                dlen != (size_t)(p - data)) {
                tlsa_free(t);
                SSLerr(SSL_F_DANE_TLSA_ADD, SSL_R_DANE_TLSA_BAD_PUBLIC_KEY);
                return 0;
            }

            /*
             * For usage DANE-TA(2), we support authentication via "2 1 0" TLSA
             * records that contain full bare keys of trust-anchors that are
             * not present in the wire chain.
             */
            if (usage == DANETLS_USAGE_DANE_TA)
                t->spki = pkey;
            else
                EVP_PKEY_free(pkey);
            break;
        }
    }

    /*-
     * Find the right insertion point for the new record.
     *
     * See crypto/x509/x509_vfy.c.  We sort DANE-EE(3) records first, so that
     * they can be processed first, as they require no chain building, and no
     * expiration or hostname checks.  Because DANE-EE(3) is numerically
     * largest, this is accomplished via descending sort by "usage".
     *
     * We also sort in descending order by matching ordinal to simplify
     * the implementation of digest agility in the verification code.
     *
     * The choice of order for the selector is not significant, so we
     * use the same descending order for consistency.
     */
    num = sk_danetls_record_num(dane->trecs);
    for (i = 0; i < num; ++i) {
        danetls_record *rec = sk_danetls_record_value(dane->trecs, i);

        if (rec->usage > usage)
            continue;
        if (rec->usage < usage)
            break;
        if (rec->selector > selector)
            continue;
        if (rec->selector < selector)
            break;
        if (dane->dctx->mdord[rec->mtype] > dane->dctx->mdord[mtype])
            continue;
        break;
    }

    if (!sk_danetls_record_insert(dane->trecs, t, i)) {
        tlsa_free(t);
        SSLerr(SSL_F_DANE_TLSA_ADD, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    dane->umask |= DANETLS_USAGE_BIT(usage);

    return 1;
}