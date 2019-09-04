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
struct fnic {unsigned long state_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline int
fnic_chk_state_flags_locked(struct fnic *fnic, unsigned long st_flags)
{
	return ((fnic->state_flags & st_flags) == st_flags);
}