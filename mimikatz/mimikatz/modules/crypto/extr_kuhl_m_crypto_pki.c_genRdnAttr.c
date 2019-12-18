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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int cbData; scalar_t__ pbData; } ;
struct TYPE_5__ {TYPE_1__ Value; int /*<<< orphan*/  dwValueType; scalar_t__ pszObjId; } ;
typedef  TYPE_2__* PCERT_RDN_ATTR ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_RDN_UNICODE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int lstrlenW (scalar_t__) ; 

BOOL genRdnAttr(PCERT_RDN_ATTR attr, LPSTR oid, LPCWSTR name)
{
	BOOL status = FALSE;
	if(attr && name && oid)
	{
		attr->pszObjId = oid;
		attr->dwValueType = CERT_RDN_UNICODE_STRING;
		attr->Value.cbData = lstrlenW(name) * sizeof(wchar_t);
		attr->Value.pbData = (PBYTE) name;
		status = TRUE;
	}
	return status;
}