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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int SECURITY_DESCRIPTOR_CONTROL ;
typedef  int /*<<< orphan*/  PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  PACL ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DumpAcl (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  DumpString (char const*,int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSecurityDescriptorControl (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSecurityDescriptorDacl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SE_DACL_AUTO_INHERITED ; 
 int SE_DACL_AUTO_INHERIT_REQ ; 
 int SE_DACL_PROTECTED ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL DumpDacl(PSECURITY_DESCRIPTOR SecurityDescriptor, WCHAR **pwptr, ULONG *plen)
{
    static const WCHAR dacl[] = {'D',':',0};
    SECURITY_DESCRIPTOR_CONTROL control;
    BOOL present, defaulted;
    DWORD revision;
    PACL pacl;

    if (!GetSecurityDescriptorDacl(SecurityDescriptor, &present, &pacl, &defaulted))
        return FALSE;

    if (!GetSecurityDescriptorControl(SecurityDescriptor, &control, &revision))
        return FALSE;

    if (!present)
        return TRUE;

    DumpString(dacl, 2, pwptr, plen);
    if (!DumpAcl(pacl, pwptr, plen, control & SE_DACL_PROTECTED, control & SE_DACL_AUTO_INHERIT_REQ, control & SE_DACL_AUTO_INHERITED))
        return FALSE;
    return TRUE;
}