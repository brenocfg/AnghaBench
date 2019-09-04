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
 scalar_t__ IS_A_TT () ; 
 int /*<<< orphan*/  scsi_falcon_intr ; 
 scalar_t__ stdma_is_locked_by (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdma_release () ; 

__attribute__((used)) static void falcon_release_lock(void)
{
	if (IS_A_TT())
		return;

	if (stdma_is_locked_by(scsi_falcon_intr))
		stdma_release();
}