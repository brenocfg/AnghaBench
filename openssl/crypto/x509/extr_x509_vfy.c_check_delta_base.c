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
struct TYPE_7__ {int /*<<< orphan*/  crl_number; int /*<<< orphan*/  base_crl_number; } ;
typedef  TYPE_1__ X509_CRL ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_authority_key_identifier ; 
 int /*<<< orphan*/  NID_issuing_distribution_point ; 
 int /*<<< orphan*/  X509_CRL_get_issuer (TYPE_1__*) ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crl_extension_match (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_delta_base(X509_CRL *delta, X509_CRL *base)
{
    /* Delta CRL must be a delta */
    if (!delta->base_crl_number)
        return 0;
    /* Base must have a CRL number */
    if (!base->crl_number)
        return 0;
    /* Issuer names must match */
    if (X509_NAME_cmp(X509_CRL_get_issuer(base), X509_CRL_get_issuer(delta)))
        return 0;
    /* AKID and IDP must match */
    if (!crl_extension_match(delta, base, NID_authority_key_identifier))
        return 0;
    if (!crl_extension_match(delta, base, NID_issuing_distribution_point))
        return 0;
    /* Delta CRL base number must not exceed Full CRL number. */
    if (ASN1_INTEGER_cmp(delta->base_crl_number, base->crl_number) > 0)
        return 0;
    /* Delta CRL number must exceed full CRL number */
    if (ASN1_INTEGER_cmp(delta->crl_number, base->crl_number) > 0)
        return 1;
    return 0;
}