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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pgd_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 

void pgd_clear_bad(pgd_t *pgd)
{
	pgd_ERROR(*pgd);
	pgd_clear(pgd);
}