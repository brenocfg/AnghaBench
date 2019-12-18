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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PCRegKeySecurity ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CRegKeySecurity_fnAddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IEffectivePermission ; 
 int /*<<< orphan*/  IID_IEffectivePermission ; 
 int /*<<< orphan*/  IID_IRegKeySecurity ; 
 int /*<<< orphan*/  IID_IRegKeySecurity2 ; 
 int /*<<< orphan*/  IID_ISecurityObjectTypeInfo ; 
 int /*<<< orphan*/  ISecurityInformation ; 
 int /*<<< orphan*/  ISecurityInformation2 ; 
 int /*<<< orphan*/  ISecurityObjectTypeInfo ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ impl_to_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline HRESULT
CRegKeySecurity_fnQueryInterface(PCRegKeySecurity obj,
                                 REFIID iid,
                                 PVOID *pvObject)
{
    PVOID pvObj = NULL;

    if (IsEqualGUID(iid,
                    &IID_IRegKeySecurity))
    {
        pvObj = (PVOID)impl_to_interface(obj,
                                         ISecurityInformation);
    }
#if REGEDIT_IMPLEMENT_ISECURITYINFORMATION2
    else if (IsEqualGUID(iid,
                         &IID_IRegKeySecurity2))
    {
        pvObj = (PVOID)impl_to_interface(obj,
                                         ISecurityInformation2);
    }
#endif
    else if (IsEqualGUID(iid,
                         &IID_IEffectivePermission))
    {
        pvObj = (PVOID)impl_to_interface(obj,
                                         IEffectivePermission);
    }
    else if (IsEqualGUID(iid,
                         &IID_ISecurityObjectTypeInfo))
    {
        pvObj = (PVOID)impl_to_interface(obj,
                                         ISecurityObjectTypeInfo);
    }

    if (pvObj == NULL)
    {
        return E_NOINTERFACE;
    }

    *pvObject = pvObj;
    CRegKeySecurity_fnAddRef(obj);

    return S_OK;
}