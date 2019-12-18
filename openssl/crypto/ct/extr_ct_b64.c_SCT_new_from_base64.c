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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ct_log_entry_type_t ;
typedef  int /*<<< orphan*/  SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_NEW_FROM_BASE64 ; 
 int /*<<< orphan*/  CT_R_SCT_UNSUPPORTED_VERSION ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SCT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SCT_new () ; 
 int /*<<< orphan*/  SCT_set0_extensions (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SCT_set0_log_id (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SCT_set_log_entry_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCT_set_timestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCT_set_version (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  X509_R_BASE64_DECODE_ERROR ; 
 int ct_base64_decode (char const*,unsigned char**) ; 
 scalar_t__ o2i_SCT_signature (int /*<<< orphan*/ *,unsigned char const**,int) ; 

SCT *SCT_new_from_base64(unsigned char version, const char *logid_base64,
                         ct_log_entry_type_t entry_type, uint64_t timestamp,
                         const char *extensions_base64,
                         const char *signature_base64)
{
    SCT *sct = SCT_new();
    unsigned char *dec = NULL;
    const unsigned char* p = NULL;
    int declen;

    if (sct == NULL) {
        CTerr(CT_F_SCT_NEW_FROM_BASE64, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /*
     * RFC6962 section 4.1 says we "MUST NOT expect this to be 0", but we
     * can only construct SCT versions that have been defined.
     */
    if (!SCT_set_version(sct, version)) {
        CTerr(CT_F_SCT_NEW_FROM_BASE64, CT_R_SCT_UNSUPPORTED_VERSION);
        goto err;
    }

    declen = ct_base64_decode(logid_base64, &dec);
    if (declen < 0) {
        CTerr(CT_F_SCT_NEW_FROM_BASE64, X509_R_BASE64_DECODE_ERROR);
        goto err;
    }
    if (!SCT_set0_log_id(sct, dec, declen))
        goto err;
    dec = NULL;

    declen = ct_base64_decode(extensions_base64, &dec);
    if (declen < 0) {
        CTerr(CT_F_SCT_NEW_FROM_BASE64, X509_R_BASE64_DECODE_ERROR);
        goto err;
    }
    SCT_set0_extensions(sct, dec, declen);
    dec = NULL;

    declen = ct_base64_decode(signature_base64, &dec);
    if (declen < 0) {
        CTerr(CT_F_SCT_NEW_FROM_BASE64, X509_R_BASE64_DECODE_ERROR);
        goto err;
    }

    p = dec;
    if (o2i_SCT_signature(sct, &p, declen) <= 0)
        goto err;
    OPENSSL_free(dec);
    dec = NULL;

    SCT_set_timestamp(sct, timestamp);

    if (!SCT_set_log_entry_type(sct, entry_type))
        goto err;

    return sct;

 err:
    OPENSSL_free(dec);
    SCT_free(sct);
    return NULL;
}