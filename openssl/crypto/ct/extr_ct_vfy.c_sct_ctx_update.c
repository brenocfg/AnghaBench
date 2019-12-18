#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ entry_type; scalar_t__ ext_len; unsigned char* ext; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {unsigned char* ihash; unsigned char* certder; size_t certderlen; int ihashlen; unsigned char* preder; size_t prederlen; } ;
typedef  TYPE_1__ SCT_CTX ;
typedef  TYPE_2__ SCT ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 scalar_t__ CT_LOG_ENTRY_TYPE_NOT_SET ; 
 scalar_t__ CT_LOG_ENTRY_TYPE_PRECERT ; 
 scalar_t__ CT_LOG_ENTRY_TYPE_X509 ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SIGNATURE_TYPE_CERT_TIMESTAMP ; 
 int /*<<< orphan*/  l2n3 (size_t,unsigned char*) ; 
 int /*<<< orphan*/  l2n8 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  s2n (scalar_t__,unsigned char*) ; 

__attribute__((used)) static int sct_ctx_update(EVP_MD_CTX *ctx, const SCT_CTX *sctx, const SCT *sct)
{
    unsigned char tmpbuf[12];
    unsigned char *p, *der;
    size_t derlen;
    /*+
     * digitally-signed struct {
     *   (1 byte) Version sct_version;
     *   (1 byte) SignatureType signature_type = certificate_timestamp;
     *   (8 bytes) uint64 timestamp;
     *   (2 bytes) LogEntryType entry_type;
     *   (? bytes) select(entry_type) {
     *     case x509_entry: ASN.1Cert;
     *     case precert_entry: PreCert;
     *   } signed_entry;
     *   (2 bytes + sct->ext_len) CtExtensions extensions;
     * }
     */
    if (sct->entry_type == CT_LOG_ENTRY_TYPE_NOT_SET)
        return 0;
    if (sct->entry_type == CT_LOG_ENTRY_TYPE_PRECERT && sctx->ihash == NULL)
        return 0;

    p = tmpbuf;
    *p++ = sct->version;
    *p++ = SIGNATURE_TYPE_CERT_TIMESTAMP;
    l2n8(sct->timestamp, p);
    s2n(sct->entry_type, p);

    if (!EVP_DigestUpdate(ctx, tmpbuf, p - tmpbuf))
        return 0;

    if (sct->entry_type == CT_LOG_ENTRY_TYPE_X509) {
        der = sctx->certder;
        derlen = sctx->certderlen;
    } else {
        if (!EVP_DigestUpdate(ctx, sctx->ihash, sctx->ihashlen))
            return 0;
        der = sctx->preder;
        derlen = sctx->prederlen;
    }

    /* If no encoding available, fatal error */
    if (der == NULL)
        return 0;

    /* Include length first */
    p = tmpbuf;
    l2n3(derlen, p);

    if (!EVP_DigestUpdate(ctx, tmpbuf, 3))
        return 0;
    if (!EVP_DigestUpdate(ctx, der, derlen))
        return 0;

    /* Add any extensions */
    p = tmpbuf;
    s2n(sct->ext_len, p);
    if (!EVP_DigestUpdate(ctx, tmpbuf, 2))
        return 0;

    if (sct->ext_len && !EVP_DigestUpdate(ctx, sct->ext, sct->ext_len))
        return 0;

    return 1;
}