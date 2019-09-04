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
struct slgt_info {unsigned int rbuf_count; unsigned int rbuf_current; int /*<<< orphan*/  rbuf_fill_level; TYPE_1__* rbufs; } ;
struct TYPE_2__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_desc_count (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rbufs(struct slgt_info *info, unsigned int i, unsigned int last)
{
	int done = 0;

	while(!done) {
		/* reset current buffer for reuse */
		info->rbufs[i].status = 0;
		set_desc_count(info->rbufs[i], info->rbuf_fill_level);
		if (i == last)
			done = 1;
		if (++i == info->rbuf_count)
			i = 0;
	}
	info->rbuf_current = i;
}