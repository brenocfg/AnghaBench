#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_7__ {int type; int length; char const* data; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_diff (int*,int*,TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ASN1_TIME_free (TYPE_1__*) ; 
#define  V_ASN1_GENERALIZEDTIME 129 
#define  V_ASN1_UTCTIME 128 
 TYPE_1__* X509_time_adj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ascii_isdigit (char const) ; 

int X509_cmp_time(const ASN1_TIME *ctm, time_t *cmp_time)
{
    static const size_t utctime_length = sizeof("YYMMDDHHMMSSZ") - 1;
    static const size_t generalizedtime_length = sizeof("YYYYMMDDHHMMSSZ") - 1;
    ASN1_TIME *asn1_cmp_time = NULL;
    int i, day, sec, ret = 0;
#ifdef CHARSET_EBCDIC
    const char upper_z = 0x5A;
#else
    const char upper_z = 'Z';
#endif
    /*
     * Note that ASN.1 allows much more slack in the time format than RFC5280.
     * In RFC5280, the representation is fixed:
     * UTCTime: YYMMDDHHMMSSZ
     * GeneralizedTime: YYYYMMDDHHMMSSZ
     *
     * We do NOT currently enforce the following RFC 5280 requirement:
     * "CAs conforming to this profile MUST always encode certificate
     *  validity dates through the year 2049 as UTCTime; certificate validity
     *  dates in 2050 or later MUST be encoded as GeneralizedTime."
     */
    switch (ctm->type) {
    case V_ASN1_UTCTIME:
        if (ctm->length != (int)(utctime_length))
            return 0;
        break;
    case V_ASN1_GENERALIZEDTIME:
        if (ctm->length != (int)(generalizedtime_length))
            return 0;
        break;
    default:
        return 0;
    }

    /**
     * Verify the format: the ASN.1 functions we use below allow a more
     * flexible format than what's mandated by RFC 5280.
     * Digit and date ranges will be verified in the conversion methods.
     */
    for (i = 0; i < ctm->length - 1; i++) {
        if (!ascii_isdigit(ctm->data[i]))
            return 0;
    }
    if (ctm->data[ctm->length - 1] != upper_z)
        return 0;

    /*
     * There is ASN1_UTCTIME_cmp_time_t but no
     * ASN1_GENERALIZEDTIME_cmp_time_t or ASN1_TIME_cmp_time_t,
     * so we go through ASN.1
     */
    asn1_cmp_time = X509_time_adj(NULL, 0, cmp_time);
    if (asn1_cmp_time == NULL)
        goto err;
    if (!ASN1_TIME_diff(&day, &sec, ctm, asn1_cmp_time))
        goto err;

    /*
     * X509_cmp_time comparison is <=.
     * The return value 0 is reserved for errors.
     */
    ret = (day >= 0 && sec >= 0) ? -1 : 1;

 err:
    ASN1_TIME_free(asn1_cmp_time);
    return ret;
}