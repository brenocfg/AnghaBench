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
 int /*<<< orphan*/  MEI_DIRNAME ; 
 int /*<<< orphan*/  dev_major ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFX_MEI_CleanUpDevNode (int num)
{
	if (num == 0)
		unregister_chrdev (dev_major, MEI_DIRNAME);
	return 0;
}