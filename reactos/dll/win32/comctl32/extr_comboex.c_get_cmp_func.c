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
typedef  int /*<<< orphan*/  cmp_func_t ;
struct TYPE_3__ {int dwExtStyle; } ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 int CBES_EX_CASESENSITIVE ; 
 int /*<<< orphan*/  lstrcmpW ; 
 int /*<<< orphan*/  lstrcmpiW ; 

__attribute__((used)) static inline cmp_func_t get_cmp_func(COMBOEX_INFO const *infoPtr)
{
    return infoPtr->dwExtStyle & CBES_EX_CASESENSITIVE ? lstrcmpW : lstrcmpiW;
}