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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ossl_intmax_t ;
typedef  enum range { ____Placeholder_range } range ;
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  X509_PURPOSE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * OBJ_txt2obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_assert (int) ; 
#define  OPT_V_ALLOW_PROXY_CERTS 159 
#define  OPT_V_ATTIME 158 
#define  OPT_V_CHECK_SS_SIG 157 
#define  OPT_V_CRL_CHECK 156 
#define  OPT_V_CRL_CHECK_ALL 155 
#define  OPT_V_EXPLICIT_POLICY 154 
#define  OPT_V_EXTENDED_CRL 153 
#define  OPT_V_IGNORE_CRITICAL 152 
#define  OPT_V_INHIBIT_ANY 151 
#define  OPT_V_INHIBIT_MAP 150 
#define  OPT_V_ISSUER_CHECKS 149 
#define  OPT_V_NO_ALT_CHAINS 148 
#define  OPT_V_NO_CHECK_TIME 147 
#define  OPT_V_PARTIAL_CHAIN 146 
#define  OPT_V_POLICY 145 
#define  OPT_V_POLICY_CHECK 144 
#define  OPT_V_POLICY_PRINT 143 
#define  OPT_V_PURPOSE 142 
#define  OPT_V_SUITEB_128 141 
#define  OPT_V_SUITEB_128_ONLY 140 
#define  OPT_V_SUITEB_192 139 
#define  OPT_V_TRUSTED_FIRST 138 
#define  OPT_V_USE_DELTAS 137 
#define  OPT_V_VERIFY_AUTH_LEVEL 136 
#define  OPT_V_VERIFY_DEPTH 135 
#define  OPT_V_VERIFY_EMAIL 134 
#define  OPT_V_VERIFY_HOSTNAME 133 
#define  OPT_V_VERIFY_IP 132 
#define  OPT_V_VERIFY_NAME 131 
#define  OPT_V_X509_STRICT 130 
#define  OPT_V__FIRST 129 
#define  OPT_V__LAST 128 
 int /*<<< orphan*/ * X509_PURPOSE_get0 (int) ; 
 int X509_PURPOSE_get_by_sname (int /*<<< orphan*/ ) ; 
 int X509_PURPOSE_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_add0_policy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_VERIFY_PARAM_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_email (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set1_ip_asc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_auth_level (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_depth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_purpose (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int X509_V_FLAG_ALLOW_PROXY_CERTS ; 
 int X509_V_FLAG_CHECK_SS_SIGNATURE ; 
 int X509_V_FLAG_CRL_CHECK ; 
 int X509_V_FLAG_CRL_CHECK_ALL ; 
 int X509_V_FLAG_EXPLICIT_POLICY ; 
 int X509_V_FLAG_EXTENDED_CRL_SUPPORT ; 
 int X509_V_FLAG_IGNORE_CRITICAL ; 
 int X509_V_FLAG_INHIBIT_ANY ; 
 int X509_V_FLAG_INHIBIT_MAP ; 
 int X509_V_FLAG_NOTIFY_POLICY ; 
 int X509_V_FLAG_NO_ALT_CHAINS ; 
 int X509_V_FLAG_NO_CHECK_TIME ; 
 int X509_V_FLAG_PARTIAL_CHAIN ; 
 int X509_V_FLAG_POLICY_CHECK ; 
 int X509_V_FLAG_SUITEB_128_LOS ; 
 int X509_V_FLAG_SUITEB_128_LOS_ONLY ; 
 int X509_V_FLAG_SUITEB_192_LOS ; 
 int X509_V_FLAG_TRUSTED_FIRST ; 
 int X509_V_FLAG_USE_DELTAS ; 
 int X509_V_FLAG_X509_STRICT ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_arg () ; 
 int /*<<< orphan*/  opt_imax (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_printf_stderr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog ; 

int opt_verify(int opt, X509_VERIFY_PARAM *vpm)
{
    int i;
    ossl_intmax_t t = 0;
    ASN1_OBJECT *otmp;
    X509_PURPOSE *xptmp;
    const X509_VERIFY_PARAM *vtmp;

    OPENSSL_assert(vpm != NULL);
    OPENSSL_assert(opt > OPT_V__FIRST);
    OPENSSL_assert(opt < OPT_V__LAST);

    switch ((enum range)opt) {
    case OPT_V__FIRST:
    case OPT_V__LAST:
        return 0;
    case OPT_V_POLICY:
        otmp = OBJ_txt2obj(opt_arg(), 0);
        if (otmp == NULL) {
            opt_printf_stderr("%s: Invalid Policy %s\n", prog, opt_arg());
            return 0;
        }
        X509_VERIFY_PARAM_add0_policy(vpm, otmp);
        break;
    case OPT_V_PURPOSE:
        /* purpose name -> purpose index */
        i = X509_PURPOSE_get_by_sname(opt_arg());
        if (i < 0) {
            opt_printf_stderr("%s: Invalid purpose %s\n", prog, opt_arg());
            return 0;
        }

        /* purpose index -> purpose object */
        xptmp = X509_PURPOSE_get0(i);

        /* purpose object -> purpose value */
        i = X509_PURPOSE_get_id(xptmp);

        if (!X509_VERIFY_PARAM_set_purpose(vpm, i)) {
            opt_printf_stderr("%s: Internal error setting purpose %s\n",
                              prog, opt_arg());
            return 0;
        }
        break;
    case OPT_V_VERIFY_NAME:
        vtmp = X509_VERIFY_PARAM_lookup(opt_arg());
        if (vtmp == NULL) {
            opt_printf_stderr("%s: Invalid verify name %s\n",
                              prog, opt_arg());
            return 0;
        }
        X509_VERIFY_PARAM_set1(vpm, vtmp);
        break;
    case OPT_V_VERIFY_DEPTH:
        i = atoi(opt_arg());
        if (i >= 0)
            X509_VERIFY_PARAM_set_depth(vpm, i);
        break;
    case OPT_V_VERIFY_AUTH_LEVEL:
        i = atoi(opt_arg());
        if (i >= 0)
            X509_VERIFY_PARAM_set_auth_level(vpm, i);
        break;
    case OPT_V_ATTIME:
        if (!opt_imax(opt_arg(), &t))
            return 0;
        if (t != (time_t)t) {
            opt_printf_stderr("%s: epoch time out of range %s\n",
                              prog, opt_arg());
            return 0;
        }
        X509_VERIFY_PARAM_set_time(vpm, (time_t)t);
        break;
    case OPT_V_VERIFY_HOSTNAME:
        if (!X509_VERIFY_PARAM_set1_host(vpm, opt_arg(), 0))
            return 0;
        break;
    case OPT_V_VERIFY_EMAIL:
        if (!X509_VERIFY_PARAM_set1_email(vpm, opt_arg(), 0))
            return 0;
        break;
    case OPT_V_VERIFY_IP:
        if (!X509_VERIFY_PARAM_set1_ip_asc(vpm, opt_arg()))
            return 0;
        break;
    case OPT_V_IGNORE_CRITICAL:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_IGNORE_CRITICAL);
        break;
    case OPT_V_ISSUER_CHECKS:
        /* NOP, deprecated */
        break;
    case OPT_V_CRL_CHECK:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_CRL_CHECK);
        break;
    case OPT_V_CRL_CHECK_ALL:
        X509_VERIFY_PARAM_set_flags(vpm,
                                    X509_V_FLAG_CRL_CHECK |
                                    X509_V_FLAG_CRL_CHECK_ALL);
        break;
    case OPT_V_POLICY_CHECK:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_POLICY_CHECK);
        break;
    case OPT_V_EXPLICIT_POLICY:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_EXPLICIT_POLICY);
        break;
    case OPT_V_INHIBIT_ANY:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_INHIBIT_ANY);
        break;
    case OPT_V_INHIBIT_MAP:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_INHIBIT_MAP);
        break;
    case OPT_V_X509_STRICT:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_X509_STRICT);
        break;
    case OPT_V_EXTENDED_CRL:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_EXTENDED_CRL_SUPPORT);
        break;
    case OPT_V_USE_DELTAS:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_USE_DELTAS);
        break;
    case OPT_V_POLICY_PRINT:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_NOTIFY_POLICY);
        break;
    case OPT_V_CHECK_SS_SIG:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_CHECK_SS_SIGNATURE);
        break;
    case OPT_V_TRUSTED_FIRST:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_TRUSTED_FIRST);
        break;
    case OPT_V_SUITEB_128_ONLY:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_SUITEB_128_LOS_ONLY);
        break;
    case OPT_V_SUITEB_128:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_SUITEB_128_LOS);
        break;
    case OPT_V_SUITEB_192:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_SUITEB_192_LOS);
        break;
    case OPT_V_PARTIAL_CHAIN:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_PARTIAL_CHAIN);
        break;
    case OPT_V_NO_ALT_CHAINS:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_NO_ALT_CHAINS);
        break;
    case OPT_V_NO_CHECK_TIME:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_NO_CHECK_TIME);
        break;
    case OPT_V_ALLOW_PROXY_CERTS:
        X509_VERIFY_PARAM_set_flags(vpm, X509_V_FLAG_ALLOW_PROXY_CERTS);
        break;
    }
    return 1;

}