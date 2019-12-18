#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t numProviders; TYPE_1__* table; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t BAD_PROVIDER_INDEX ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* providerTable ; 

__attribute__((used)) static DWORD _findProviderIndexW(LPCWSTR lpProvider)
{
    DWORD ret = BAD_PROVIDER_INDEX;

    if (providerTable && providerTable->numProviders)
    {
        DWORD i;

        for (i = 0; i < providerTable->numProviders &&
         ret == BAD_PROVIDER_INDEX; i++)
            if (!lstrcmpW(lpProvider, providerTable->table[i].name))
                ret = i;
    }
    return ret;
}