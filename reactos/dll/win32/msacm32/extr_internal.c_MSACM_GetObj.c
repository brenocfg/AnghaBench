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
typedef  int /*<<< orphan*/  WINE_ACMOBJ ;
struct TYPE_4__ {scalar_t__ dwType; } ;
typedef  TYPE_1__* PWINE_ACMOBJ ;
typedef  int /*<<< orphan*/  HACMOBJ ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ IsBadReadPtr (TYPE_1__*,int) ; 
 scalar_t__ WINE_ACMOBJ_DONTCARE ; 

PWINE_ACMOBJ MSACM_GetObj(HACMOBJ hObj, DWORD type)
{
    PWINE_ACMOBJ	pao = (PWINE_ACMOBJ)hObj;

    if (pao == NULL || IsBadReadPtr(pao, sizeof(WINE_ACMOBJ)) ||
	((type != WINE_ACMOBJ_DONTCARE) && (type != pao->dwType)))
	return NULL;
    return pao;
}