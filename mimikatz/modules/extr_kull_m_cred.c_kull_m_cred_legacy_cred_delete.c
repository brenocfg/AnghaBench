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
struct TYPE_4__ {int /*<<< orphan*/  AttributeCount; scalar_t__ Attributes; struct TYPE_4__* CredentialBlob; struct TYPE_4__* UserName; struct TYPE_4__* TargetAlias; struct TYPE_4__* Comment; struct TYPE_4__* TargetName; } ;
typedef  TYPE_1__* PKULL_M_CRED_LEGACY_CRED_BLOB ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_cred_attributes_delete (scalar_t__,int /*<<< orphan*/ ) ; 

void kull_m_cred_legacy_cred_delete(PKULL_M_CRED_LEGACY_CRED_BLOB cred)
{
	if(cred)
	{
		if(cred->TargetName)
			LocalFree(cred->TargetName);
		if(cred->Comment)
			LocalFree(cred->Comment);
		if(cred->TargetAlias)
			LocalFree(cred->TargetAlias);
		if(cred->UserName)
			LocalFree(cred->UserName);
		if(cred->CredentialBlob)
			LocalFree(cred->CredentialBlob);
		if(cred->Attributes)
			kull_m_cred_attributes_delete(cred->Attributes, cred->AttributeCount);
		LocalFree(cred);
	}
}