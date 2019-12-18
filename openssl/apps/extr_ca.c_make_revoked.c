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
typedef  int /*<<< orphan*/  X509_REVOKED ;
typedef  int /*<<< orphan*/  ASN1_TIME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;
typedef  int /*<<< orphan*/  ASN1_ENUMERATED ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ENUMERATED_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_ENUMERATED_new () ; 
 int /*<<< orphan*/  ASN1_ENUMERATED_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_TIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_crl_reason ; 
 int /*<<< orphan*/  NID_hold_instruction_code ; 
 int /*<<< orphan*/  NID_invalidity_date ; 
 int OCSP_REVOKED_STATUS_NOSTATUS ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  X509_REVOKED_add1_ext_i2d (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_REVOKED_set_revocationDate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int unpack_revinfo (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*) ; 

__attribute__((used)) static int make_revoked(X509_REVOKED *rev, const char *str)
{
    char *tmp = NULL;
    int reason_code = -1;
    int i, ret = 0;
    ASN1_OBJECT *hold = NULL;
    ASN1_GENERALIZEDTIME *comp_time = NULL;
    ASN1_ENUMERATED *rtmp = NULL;

    ASN1_TIME *revDate = NULL;

    i = unpack_revinfo(&revDate, &reason_code, &hold, &comp_time, str);

    if (i == 0)
        goto end;

    if (rev && !X509_REVOKED_set_revocationDate(rev, revDate))
        goto end;

    if (rev && (reason_code != OCSP_REVOKED_STATUS_NOSTATUS)) {
        rtmp = ASN1_ENUMERATED_new();
        if (rtmp == NULL || !ASN1_ENUMERATED_set(rtmp, reason_code))
            goto end;
        if (!X509_REVOKED_add1_ext_i2d(rev, NID_crl_reason, rtmp, 0, 0))
            goto end;
    }

    if (rev && comp_time) {
        if (!X509_REVOKED_add1_ext_i2d
            (rev, NID_invalidity_date, comp_time, 0, 0))
            goto end;
    }
    if (rev && hold) {
        if (!X509_REVOKED_add1_ext_i2d
            (rev, NID_hold_instruction_code, hold, 0, 0))
            goto end;
    }

    if (reason_code != OCSP_REVOKED_STATUS_NOSTATUS)
        ret = 2;
    else
        ret = 1;

 end:

    OPENSSL_free(tmp);
    ASN1_OBJECT_free(hold);
    ASN1_GENERALIZEDTIME_free(comp_time);
    ASN1_ENUMERATED_free(rtmp);
    ASN1_TIME_free(revDate);

    return ret;
}