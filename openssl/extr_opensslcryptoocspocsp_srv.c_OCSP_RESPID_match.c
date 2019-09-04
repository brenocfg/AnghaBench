#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int /*<<< orphan*/ * byName; int /*<<< orphan*/ * byKey; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ value; } ;
typedef  TYPE_2__ OCSP_RESPID ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int SHA_DIGEST_LENGTH ; 
 scalar_t__ V_OCSP_RESPID_KEY ; 
 scalar_t__ V_OCSP_RESPID_NAME ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_pubkey_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 

int OCSP_RESPID_match(OCSP_RESPID *respid, X509 *cert)
{
    if (respid->type == V_OCSP_RESPID_KEY) {
        unsigned char md[SHA_DIGEST_LENGTH];

        if (respid->value.byKey == NULL)
            return 0;

        /* RFC2560 requires SHA1 */
        if (!X509_pubkey_digest(cert, EVP_sha1(), md, NULL))
            return 0;

        return (ASN1_STRING_length(respid->value.byKey) == SHA_DIGEST_LENGTH)
            && (memcmp(ASN1_STRING_get0_data(respid->value.byKey), md,
                       SHA_DIGEST_LENGTH) == 0);
    } else if (respid->type == V_OCSP_RESPID_NAME) {
        if (respid->value.byName == NULL)
            return 0;

        return X509_NAME_cmp(respid->value.byName,
                             X509_get_subject_name(cert)) == 0;
    }

    return 0;
}