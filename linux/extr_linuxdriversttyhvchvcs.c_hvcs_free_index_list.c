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
 scalar_t__ hvcs_index_count ; 
 int /*<<< orphan*/ * hvcs_index_list ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvcs_free_index_list(void)
{
	/* Paranoia check to be thorough. */
	kfree(hvcs_index_list);
	hvcs_index_list = NULL;
	hvcs_index_count = 0;
}