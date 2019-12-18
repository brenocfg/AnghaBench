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
typedef  int /*<<< orphan*/  ASN1_TIME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_new () ; 
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_UTCTIME_new () ; 
 int /*<<< orphan*/  ASN1_UTCTIME_set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int NUM_REASONS ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char*,int /*<<< orphan*/ ) ; 
 int OCSP_REVOKED_STATUS_CACOMPROMISE ; 
 int OCSP_REVOKED_STATUS_CERTIFICATEHOLD ; 
 int OCSP_REVOKED_STATUS_KEYCOMPROMISE ; 
 int OCSP_REVOKED_STATUS_NOSTATUS ; 
 int OCSP_REVOKED_STATUS_REMOVEFROMCRL ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * crl_reasons ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

int unpack_revinfo(ASN1_TIME **prevtm, int *preason, ASN1_OBJECT **phold,
                   ASN1_GENERALIZEDTIME **pinvtm, const char *str)
{
    char *tmp;
    char *rtime_str, *reason_str = NULL, *arg_str = NULL, *p;
    int reason_code = -1;
    int ret = 0;
    unsigned int i;
    ASN1_OBJECT *hold = NULL;
    ASN1_GENERALIZEDTIME *comp_time = NULL;

    tmp = OPENSSL_strdup(str);
    if (!tmp) {
        BIO_printf(bio_err, "memory allocation failure\n");
        goto end;
    }

    p = strchr(tmp, ',');

    rtime_str = tmp;

    if (p) {
        *p = '\0';
        p++;
        reason_str = p;
        p = strchr(p, ',');
        if (p) {
            *p = '\0';
            arg_str = p + 1;
        }
    }

    if (prevtm) {
        *prevtm = ASN1_UTCTIME_new();
        if (*prevtm == NULL) {
            BIO_printf(bio_err, "memory allocation failure\n");
            goto end;
        }
        if (!ASN1_UTCTIME_set_string(*prevtm, rtime_str)) {
            BIO_printf(bio_err, "invalid revocation date %s\n", rtime_str);
            goto end;
        }
    }
    if (reason_str) {
        for (i = 0; i < NUM_REASONS; i++) {
            if (strcasecmp(reason_str, crl_reasons[i]) == 0) {
                reason_code = i;
                break;
            }
        }
        if (reason_code == OCSP_REVOKED_STATUS_NOSTATUS) {
            BIO_printf(bio_err, "invalid reason code %s\n", reason_str);
            goto end;
        }

        if (reason_code == 7) {
            reason_code = OCSP_REVOKED_STATUS_REMOVEFROMCRL;
        } else if (reason_code == 8) { /* Hold instruction */
            if (!arg_str) {
                BIO_printf(bio_err, "missing hold instruction\n");
                goto end;
            }
            reason_code = OCSP_REVOKED_STATUS_CERTIFICATEHOLD;
            hold = OBJ_txt2obj(arg_str, 0);

            if (!hold) {
                BIO_printf(bio_err, "invalid object identifier %s\n", arg_str);
                goto end;
            }
            if (phold)
                *phold = hold;
            else
                ASN1_OBJECT_free(hold);
        } else if ((reason_code == 9) || (reason_code == 10)) {
            if (!arg_str) {
                BIO_printf(bio_err, "missing compromised time\n");
                goto end;
            }
            comp_time = ASN1_GENERALIZEDTIME_new();
            if (comp_time == NULL) {
                BIO_printf(bio_err, "memory allocation failure\n");
                goto end;
            }
            if (!ASN1_GENERALIZEDTIME_set_string(comp_time, arg_str)) {
                BIO_printf(bio_err, "invalid compromised time %s\n", arg_str);
                goto end;
            }
            if (reason_code == 9)
                reason_code = OCSP_REVOKED_STATUS_KEYCOMPROMISE;
            else
                reason_code = OCSP_REVOKED_STATUS_CACOMPROMISE;
        }
    }

    if (preason)
        *preason = reason_code;
    if (pinvtm) {
        *pinvtm = comp_time;
        comp_time = NULL;
    }

    ret = 1;

 end:

    OPENSSL_free(tmp);
    ASN1_GENERALIZEDTIME_free(comp_time);

    return ret;
}