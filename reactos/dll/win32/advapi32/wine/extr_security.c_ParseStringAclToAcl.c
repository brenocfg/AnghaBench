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
struct TYPE_5__ {int AceSize; void* AceFlags; void* AceType; } ;
struct TYPE_7__ {int Mask; TYPE_1__ Header; int /*<<< orphan*/  SidStart; } ;
struct TYPE_6__ {int AclSize; int AceCount; scalar_t__ Sbz2; scalar_t__ Sbz1; int /*<<< orphan*/  AclRevision; } ;
typedef  TYPE_2__* PACL ;
typedef  TYPE_3__* PACCESS_ALLOWED_ACE ;
typedef  int* LPDWORD ;
typedef  char* LPCWSTR ;
typedef  int LPBYTE ;
typedef  int DWORD ;
typedef  void* BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ACL ;
typedef  int /*<<< orphan*/  ACCESS_ALLOWED_ACE ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int ERROR_INVALID_ACL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int ParseAceStringFlags (char**) ; 
 int ParseAceStringRights (char**) ; 
 int ParseAceStringType (char**) ; 
 int ParseAclStringFlags (char**) ; 
 scalar_t__ ParseStringSidToSid (char*,int /*<<< orphan*/ *,int*) ; 
 int RPC_S_INVALID_STRING_UUID ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 

__attribute__((used)) static BOOL ParseStringAclToAcl(LPCWSTR StringAcl, LPDWORD lpdwFlags, 
    PACL pAcl, LPDWORD cBytes)
{
    DWORD val;
    DWORD sidlen;
    DWORD length = sizeof(ACL);
    DWORD acesize = 0;
    DWORD acecount = 0;
    PACCESS_ALLOWED_ACE pAce = NULL; /* pointer to current ACE */
    DWORD error = ERROR_INVALID_ACL;

    TRACE("%s\n", debugstr_w(StringAcl));

    if (!StringAcl)
	return FALSE;

    if (pAcl) /* pAce is only useful if we're setting values */
        pAce = (PACCESS_ALLOWED_ACE) (pAcl + 1);

    /* Parse ACL flags */
    *lpdwFlags = ParseAclStringFlags(&StringAcl);

    /* Parse ACE */
    while (*StringAcl == '(')
    {
        StringAcl++;

        /* Parse ACE type */
        val = ParseAceStringType(&StringAcl);
	if (pAce)
            pAce->Header.AceType = (BYTE) val;
        if (*StringAcl != ';')
        {
            error = RPC_S_INVALID_STRING_UUID;
            goto lerr;
        }
        StringAcl++;

        /* Parse ACE flags */
	val = ParseAceStringFlags(&StringAcl);
	if (pAce)
            pAce->Header.AceFlags = (BYTE) val;
        if (*StringAcl != ';')
            goto lerr;
        StringAcl++;

        /* Parse ACE rights */
	val = ParseAceStringRights(&StringAcl);
	if (pAce)
            pAce->Mask = val;
        if (*StringAcl != ';')
            goto lerr;
        StringAcl++;

        /* Parse ACE object guid */
        while (*StringAcl == ' ')
            StringAcl++;
        if (*StringAcl != ';')
        {
            FIXME("Support for *_OBJECT_ACE_TYPE not implemented\n");
            goto lerr;
        }
        StringAcl++;

        /* Parse ACE inherit object guid */
        while (*StringAcl == ' ')
            StringAcl++;
        if (*StringAcl != ';')
        {
            FIXME("Support for *_OBJECT_ACE_TYPE not implemented\n");
            goto lerr;
        }
        StringAcl++;

        /* Parse ACE account sid */
        if (ParseStringSidToSid(StringAcl, pAce ? &pAce->SidStart : NULL, &sidlen))
	{
            while (*StringAcl && *StringAcl != ')')
                StringAcl++;
	}

        if (*StringAcl != ')')
            goto lerr;
        StringAcl++;

        acesize = sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + sidlen;
        length += acesize;
        if (pAce)
        {
            pAce->Header.AceSize = acesize;
            pAce = (PACCESS_ALLOWED_ACE)((LPBYTE)pAce + acesize);
        }
        acecount++;
    }

    *cBytes = length;

    if (length > 0xffff)
    {
        ERR("ACL too large\n");
        goto lerr;
    }

    if (pAcl)
    {
        pAcl->AclRevision = ACL_REVISION;
        pAcl->Sbz1 = 0;
        pAcl->AclSize = length;
        pAcl->AceCount = acecount;
        pAcl->Sbz2 = 0;
    }
    return TRUE;

lerr:
    SetLastError(error);
    WARN("Invalid ACE string format\n");
    return FALSE;
}