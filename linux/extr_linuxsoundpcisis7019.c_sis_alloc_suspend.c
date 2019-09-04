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
struct sis7019 {int /*<<< orphan*/ * suspend_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SIS_SUSPEND_PAGES ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sis_alloc_suspend(struct sis7019 *sis)
{
	int i;

	/* We need 16K to store the internal wave engine state during a
	 * suspend, but we don't need it to be contiguous, so play nice
	 * with the memory system. We'll also use this area for a silence
	 * buffer.
	 */
	for (i = 0; i < SIS_SUSPEND_PAGES; i++) {
		sis->suspend_state[i] = kmalloc(4096, GFP_KERNEL);
		if (!sis->suspend_state[i])
			return -ENOMEM;
	}
	memset(sis->suspend_state[0], 0, 4096);

	return 0;
}