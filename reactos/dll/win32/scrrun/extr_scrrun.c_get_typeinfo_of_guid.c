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
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  load_typelib () ; 
 int /*<<< orphan*/  typelib ; 

__attribute__((used)) static HRESULT get_typeinfo_of_guid(const GUID *guid, ITypeInfo **tinfo)
{
    HRESULT hres;

    if(FAILED(hres = load_typelib()))
        return hres;

    return ITypeLib_GetTypeInfoOfGuid(typelib, guid, tinfo);
}