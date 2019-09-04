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
 int /*<<< orphan*/  nlm_traverse_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_is_client ; 

void
nlmsvc_invalidate_all(void)
{
	/*
	 * Previously, the code would call
	 * nlmsvc_free_host_resources for each client in
	 * turn, which is about as inefficient as it gets.
	 * Now we just do it once in nlm_traverse_files.
	 */
	nlm_traverse_files(NULL, nlmsvc_is_client, NULL);
}