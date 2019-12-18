#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  catmgr; scalar_t__ langkey; scalar_t__ tipkey; } ;
typedef  TYPE_1__ EnumTfLanguageProfiles ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ITfCategoryMgr_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static void EnumTfLanguageProfiles_Destructor(EnumTfLanguageProfiles *This)
{
    TRACE("destroying %p\n", This);
    RegCloseKey(This->tipkey);
    if (This->langkey)
        RegCloseKey(This->langkey);
    ITfCategoryMgr_Release(This->catmgr);
    HeapFree(GetProcessHeap(),0,This);
}