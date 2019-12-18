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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_KPAGECOUNT ; 
 unsigned long do_u64_read (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 scalar_t__ kpagecount_fd ; 

__attribute__((used)) static unsigned long kpagecount_read(uint64_t *buf,
				     unsigned long index,
				     unsigned long pages)
{
	return kpagecount_fd < 0 ? pages :
		do_u64_read(kpagecount_fd, PROC_KPAGECOUNT,
			    buf, index, pages);
}