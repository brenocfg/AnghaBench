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
 unsigned long do_u64_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kpageflags_fd ; 
 int /*<<< orphan*/  opt_kpageflags ; 

__attribute__((used)) static unsigned long kpageflags_read(uint64_t *buf,
				     unsigned long index,
				     unsigned long pages)
{
	return do_u64_read(kpageflags_fd, opt_kpageflags, buf, index, pages);
}