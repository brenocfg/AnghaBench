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
typedef  scalar_t__ uint64_t ;
struct file_lock {scalar_t__ fl_end; scalar_t__ fl_start; } ;

/* Variables and functions */
 scalar_t__ OFFSET_MAX ; 

__attribute__((used)) static inline uint64_t nfs4_lock_length(struct file_lock *fl)
{
	if (fl->fl_end == OFFSET_MAX)
		return ~(uint64_t)0;
	return fl->fl_end - fl->fl_start + 1;
}