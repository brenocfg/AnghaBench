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
struct TYPE_5__ {size_t cPolicyInfo; TYPE_1__* rgPolicyInfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  pszPolicyIdentifier; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CERT_POLICIES_INFO ;
typedef  int /*<<< orphan*/  CERT_INFO ;

/* Variables and functions */
 size_t CERT_TRUST_INVALID_POLICY_CONSTRAINTS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_ANY_CERT_POLICY ; 

__attribute__((used)) static void CRYPT_CheckPolicies(const CERT_POLICIES_INFO *policies, CERT_INFO *cert,
 DWORD *errorStatus)
{
    DWORD i;

    for (i = 0; i < policies->cPolicyInfo; i++)
    {
        /* For now, the only accepted policy identifier is the anyPolicy
         * identifier.
         * FIXME: the policy identifiers should be compared against the
         * cert's certificate policies extension, subject to the policy
         * mappings extension, and the policy constraints extension.
         * See RFC 5280, sections 4.2.1.4, 4.2.1.5, and 4.2.1.11.
         */
        if (strcmp(policies->rgPolicyInfo[i].pszPolicyIdentifier,
         szOID_ANY_CERT_POLICY))
        {
            FIXME("unsupported policy %s\n",
             policies->rgPolicyInfo[i].pszPolicyIdentifier);
            *errorStatus |= CERT_TRUST_INVALID_POLICY_CONSTRAINTS;
        }
    }
}