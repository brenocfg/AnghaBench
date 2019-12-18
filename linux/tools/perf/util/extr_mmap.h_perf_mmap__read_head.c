#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct mmap {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ring_buffer_read_head (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 perf_mmap__read_head(struct mmap *mm)
{
	return ring_buffer_read_head(mm->core.base);
}