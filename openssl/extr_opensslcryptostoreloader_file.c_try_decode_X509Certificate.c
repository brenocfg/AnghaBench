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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/ * OSSL_STORE_INFO_new_CERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_STRING_X509 ; 
 int /*<<< orphan*/  PEM_STRING_X509_OLD ; 
 int /*<<< orphan*/  PEM_STRING_X509_TRUSTED ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/ * d2i_X509_AUX (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSSL_STORE_INFO *try_decode_X509Certificate(const char *pem_name,
                                                   const char *pem_header,
                                                   const unsigned char *blob,
                                                   size_t len, void **pctx,
                                                   int *matchcount,
                                                   const UI_METHOD *ui_method,
                                                   void *ui_data)
{
    OSSL_STORE_INFO *store_info = NULL;
    X509 *cert = NULL;

    /*
     * In most cases, we can try to interpret the serialized data as a trusted
     * cert (X509 + X509_AUX) and fall back to reading it as a normal cert
     * (just X509), but if the PEM name specifically declares it as a trusted
     * cert, then no fallback should be engaged.  |ignore_trusted| tells if
     * the fallback can be used (1) or not (0).
     */
    int ignore_trusted = 1;

    if (pem_name != NULL) {
        if (strcmp(pem_name, PEM_STRING_X509_TRUSTED) == 0)
            ignore_trusted = 0;
        else if (strcmp(pem_name, PEM_STRING_X509_OLD) != 0
                 && strcmp(pem_name, PEM_STRING_X509) != 0)
            /* No match */
            return NULL;
        *matchcount = 1;
    }

    if ((cert = d2i_X509_AUX(NULL, &blob, len)) != NULL
        || (ignore_trusted && (cert = d2i_X509(NULL, &blob, len)) != NULL)) {
        *matchcount = 1;
        store_info = OSSL_STORE_INFO_new_CERT(cert);
    }

    if (store_info == NULL)
        X509_free(cert);

    return store_info;
}