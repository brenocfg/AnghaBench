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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  CTLOG ;

/* Variables and functions */
 int /*<<< orphan*/ * CTLOG_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  CT_F_CTLOG_NEW_FROM_BASE64 ; 
 int /*<<< orphan*/  CT_R_LOG_CONF_INVALID_KEY ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int ct_base64_decode (char const*,unsigned char**) ; 
 int /*<<< orphan*/ * d2i_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,int) ; 

int CTLOG_new_from_base64(CTLOG **ct_log, const char *pkey_base64, const char *name)
{
    unsigned char *pkey_der = NULL;
    int pkey_der_len;
    const unsigned char *p;
    EVP_PKEY *pkey = NULL;

    if (ct_log == NULL) {
        CTerr(CT_F_CTLOG_NEW_FROM_BASE64, ERR_R_PASSED_INVALID_ARGUMENT);
        return 0;
    }

    pkey_der_len = ct_base64_decode(pkey_base64, &pkey_der);
    if (pkey_der_len < 0) {
        CTerr(CT_F_CTLOG_NEW_FROM_BASE64, CT_R_LOG_CONF_INVALID_KEY);
        return 0;
    }

    p = pkey_der;
    pkey = d2i_PUBKEY(NULL, &p, pkey_der_len);
    OPENSSL_free(pkey_der);
    if (pkey == NULL) {
        CTerr(CT_F_CTLOG_NEW_FROM_BASE64, CT_R_LOG_CONF_INVALID_KEY);
        return 0;
    }

    *ct_log = CTLOG_new(pkey, name);
    if (*ct_log == NULL) {
        EVP_PKEY_free(pkey);
        return 0;
    }

    return 1;
}