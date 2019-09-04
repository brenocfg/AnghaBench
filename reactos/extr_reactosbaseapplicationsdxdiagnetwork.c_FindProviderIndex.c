#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Guid; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ DIRECTPLAY_GUID ;

/* Variables and functions */
 int UINT_MAX ; 
 int /*<<< orphan*/  wcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

UINT
FindProviderIndex(LPCWSTR szGuid, DIRECTPLAY_GUID * PreDefProviders)
{
    UINT Index;
    for(Index = 0; Index < 4; Index++)
    {
        if (!wcsncmp(PreDefProviders[Index].Guid, szGuid, 40))
            return Index;
    }
    return UINT_MAX;
}