#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cEntries; int /*<<< orphan*/ * pse; } ;
struct TYPE_5__ {size_t cEntries; int /*<<< orphan*/ * pse; } ;
typedef  TYPE_1__ STRTABLEW ;
typedef  TYPE_2__ STRTABLEA ;
typedef  int /*<<< orphan*/  STRENTRYW ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strentry_atow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static STRTABLEW *strtable_atow(const STRTABLEA *atable)
{
    STRTABLEW *wtable;
    DWORD j;

    wtable = HeapAlloc(GetProcessHeap(), 0, sizeof(STRTABLEW));
    wtable->pse = HeapAlloc(GetProcessHeap(), 0, atable->cEntries * sizeof(STRENTRYW));
    wtable->cEntries = atable->cEntries;

    for (j = 0; j < wtable->cEntries; j++)
        strentry_atow(&atable->pse[j], &wtable->pse[j]);

    return wtable;
}