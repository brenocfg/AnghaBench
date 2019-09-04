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
 int NUM_BUFS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bufs_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bufs_in ; 
 int /*<<< orphan*/ * bufs_out ; 

__attribute__((used)) static void bufs_confirm(void)
{
	int i, j;

	for (i = 0; i < NUM_BUFS; i++) {
		int matches = 0;

		for (j = 0; j < NUM_BUFS; j++)
			if (!bufs_cmp(&bufs_in[i], &bufs_out[j]))
				matches++;
		WARN_ON(matches != 1);
	}
}