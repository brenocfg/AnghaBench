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
typedef  int /*<<< orphan*/  sig_atomic_t ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  MaxLivePostmasterChildren () ; 
 int /*<<< orphan*/  PMChildFlags ; 
 int /*<<< orphan*/  PMSignalData ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Size
PMSignalShmemSize(void)
{
	Size		size;

	size = offsetof(PMSignalData, PMChildFlags);
	size = add_size(size, mul_size(MaxLivePostmasterChildren(),
								   sizeof(sig_atomic_t)));

	return size;
}