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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmd_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 

void pmd_clear_bad(pmd_t *pmd)
{
	pmd_ERROR(*pmd);
	pmd_clear(pmd);
}