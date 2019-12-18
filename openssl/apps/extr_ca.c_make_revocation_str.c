#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; scalar_t__ data; } ;
typedef  int REVINFO_TYPE ;
typedef  TYPE_1__ ASN1_UTCTIME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_set_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_UTCTIME_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,int) ; 
#define  REV_CA_COMPROMISE 133 
#define  REV_CRL_REASON 132 
#define  REV_HOLD 131 
#define  REV_KEY_COMPROMISE 130 
#define  REV_NONE 129 
#define  REV_VALID 128 
 TYPE_1__* X509_gmtime_adj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 char** crl_reasons ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *make_revocation_str(REVINFO_TYPE rev_type, const char *rev_arg)
{
    char *str;
    const char *reason = NULL, *other = NULL;
    ASN1_OBJECT *otmp;
    ASN1_UTCTIME *revtm = NULL;
    int i;

    switch (rev_type) {
    case REV_NONE:
    case REV_VALID:
        break;

    case REV_CRL_REASON:
        for (i = 0; i < 8; i++) {
            if (strcasecmp(rev_arg, crl_reasons[i]) == 0) {
                reason = crl_reasons[i];
                break;
            }
        }
        if (reason == NULL) {
            BIO_printf(bio_err, "Unknown CRL reason %s\n", rev_arg);
            return NULL;
        }
        break;

    case REV_HOLD:
        /* Argument is an OID */
        otmp = OBJ_txt2obj(rev_arg, 0);
        ASN1_OBJECT_free(otmp);

        if (otmp == NULL) {
            BIO_printf(bio_err, "Invalid object identifier %s\n", rev_arg);
            return NULL;
        }

        reason = "holdInstruction";
        other = rev_arg;
        break;

    case REV_KEY_COMPROMISE:
    case REV_CA_COMPROMISE:
        /* Argument is the key compromise time  */
        if (!ASN1_GENERALIZEDTIME_set_string(NULL, rev_arg)) {
            BIO_printf(bio_err,
                       "Invalid time format %s. Need YYYYMMDDHHMMSSZ\n",
                       rev_arg);
            return NULL;
        }
        other = rev_arg;
        if (rev_type == REV_KEY_COMPROMISE)
            reason = "keyTime";
        else
            reason = "CAkeyTime";

        break;
    }

    revtm = X509_gmtime_adj(NULL, 0);

    if (!revtm)
        return NULL;

    i = revtm->length + 1;

    if (reason)
        i += strlen(reason) + 1;
    if (other)
        i += strlen(other) + 1;

    str = app_malloc(i, "revocation reason");
    OPENSSL_strlcpy(str, (char *)revtm->data, i);
    if (reason) {
        OPENSSL_strlcat(str, ",", i);
        OPENSSL_strlcat(str, reason, i);
    }
    if (other) {
        OPENSSL_strlcat(str, ",", i);
        OPENSSL_strlcat(str, other, i);
    }
    ASN1_UTCTIME_free(revtm);
    return str;
}