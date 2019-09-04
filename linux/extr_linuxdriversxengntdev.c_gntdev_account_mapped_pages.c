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

/* Variables and functions */
 scalar_t__ atomic_add_return (int,int /*<<< orphan*/ *) ; 
 scalar_t__ limit ; 
 int /*<<< orphan*/  pages_mapped ; 

bool gntdev_account_mapped_pages(int count)
{
	return atomic_add_return(count, &pages_mapped) > limit;
}