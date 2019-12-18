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
typedef  int /*<<< orphan*/  OSSL_CMP_PKIFREETEXT ;
typedef  int /*<<< orphan*/  OSSL_CMP_CTX ;
typedef  int /*<<< orphan*/  ASN1_UTF8STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_BUFFER ; 
 char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int BIO_snprintf (char*,size_t,char*,...) ; 
 char* CMP_PKIFAILUREINFO_to_string (int) ; 
 int /*<<< orphan*/ * OSSL_CMP_CTX_get0_statusString (int /*<<< orphan*/ *) ; 
 int OSSL_CMP_CTX_get_failInfoCode (int /*<<< orphan*/ *) ; 
 int OSSL_CMP_CTX_get_status (int /*<<< orphan*/ *) ; 
 int OSSL_CMP_PKIFAILUREINFO_MAX ; 
 int OSSL_CMP_PKISTATUS_accepted ; 
 int OSSL_CMP_PKISTATUS_grantedWithMods ; 
 char* ossl_cmp_PKIStatus_to_string (int) ; 
 int sk_ASN1_UTF8STRING_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ASN1_UTF8STRING_value (int /*<<< orphan*/ *,int) ; 

char *OSSL_CMP_CTX_snprint_PKIStatus(OSSL_CMP_CTX *ctx, char *buf,
                                     size_t bufsize)
{
    int status, failure, fail_info;
    const char *status_string, *failure_string;
    OSSL_CMP_PKIFREETEXT *status_strings;
    ASN1_UTF8STRING *text;
    int i;
    int printed_chars;
    int failinfo_found = 0;
    int n_status_strings;
    char* write_ptr = buf;

#define ADVANCE_BUFFER                                         \
    if (printed_chars < 0 || (size_t)printed_chars >= bufsize) \
        return NULL; \
    write_ptr += printed_chars; \
    bufsize -= printed_chars;

    if (ctx == NULL
            || buf == NULL
            || (status = OSSL_CMP_CTX_get_status(ctx)) < 0
            || (status_string = ossl_cmp_PKIStatus_to_string(status)) == NULL)
        return NULL;
    printed_chars = BIO_snprintf(write_ptr, bufsize, "%s", status_string);
    ADVANCE_BUFFER;

    /* failInfo is optional and may be empty */
    if ((fail_info = OSSL_CMP_CTX_get_failInfoCode(ctx)) > 0) {
        printed_chars = BIO_snprintf(write_ptr, bufsize, "; PKIFailureInfo: ");
        ADVANCE_BUFFER;
        for (failure = 0; failure <= OSSL_CMP_PKIFAILUREINFO_MAX; failure++) {
            if ((fail_info & (1 << failure)) != 0) {
                failure_string = CMP_PKIFAILUREINFO_to_string(failure);
                if (failure_string != NULL) {
                    printed_chars = BIO_snprintf(write_ptr, bufsize, "%s%s",
                                                 failure > 0 ? ", " : "",
                                                 failure_string);
                    ADVANCE_BUFFER;
                    failinfo_found = 1;
                }
            }
        }
    }
    if (!failinfo_found && status != OSSL_CMP_PKISTATUS_accepted
            && status != OSSL_CMP_PKISTATUS_grantedWithMods) {
        printed_chars = BIO_snprintf(write_ptr, bufsize, "; <no failure info>");
        ADVANCE_BUFFER;
    }

    /* statusString sequence is optional and may be empty */
    status_strings = OSSL_CMP_CTX_get0_statusString(ctx);
    n_status_strings = sk_ASN1_UTF8STRING_num(status_strings);
    if (n_status_strings > 0) {
        printed_chars = BIO_snprintf(write_ptr, bufsize, "; StatusString%s: ",
                                     n_status_strings > 1 ? "s" : "");
        ADVANCE_BUFFER;
        for (i = 0; i < n_status_strings; i++) {
            text = sk_ASN1_UTF8STRING_value(status_strings, i);
            printed_chars = BIO_snprintf(write_ptr, bufsize, "\"%s\"%s",
                                         ASN1_STRING_get0_data(text),
                                         i < n_status_strings - 1 ? ", " : "");
            ADVANCE_BUFFER;
        }
    }
#undef ADVANCE_BUFFER
    return buf;
}