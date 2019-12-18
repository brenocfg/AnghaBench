#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t cPolicyInfo; TYPE_2__* rgPolicyInfo; } ;
struct TYPE_6__ {size_t cPolicyQualifier; TYPE_1__* rgPolicyQualifier; } ;
struct TYPE_5__ {int /*<<< orphan*/  Qualifier; int /*<<< orphan*/  pszPolicyQualifierId; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CRYPT_OBJID_BLOB ;
typedef  TYPE_3__ CERT_POLICIES_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CRYPT_OBJID_BLOB *find_policy_qualifier(CERT_POLICIES_INFO *policies,
 LPCSTR policyOid)
{
    CRYPT_OBJID_BLOB *ret = NULL;
    DWORD i;

    for (i = 0; !ret && i < policies->cPolicyInfo; i++)
    {
        DWORD j;

        for (j = 0; !ret && j < policies->rgPolicyInfo[i].cPolicyQualifier; j++)
            if (!strcmp(policies->rgPolicyInfo[i].rgPolicyQualifier[j].
             pszPolicyQualifierId, policyOid))
                ret = &policies->rgPolicyInfo[i].rgPolicyQualifier[j].
                 Qualifier;
    }
    return ret;
}