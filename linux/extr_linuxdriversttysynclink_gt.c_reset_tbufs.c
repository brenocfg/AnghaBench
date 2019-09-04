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
struct slgt_info {unsigned int tbuf_count; TYPE_1__* tbufs; scalar_t__ tbuf_current; } ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ status; } ;

/* Variables and functions */

__attribute__((used)) static void reset_tbufs(struct slgt_info *info)
{
	unsigned int i;
	info->tbuf_current = 0;
	for (i=0 ; i < info->tbuf_count ; i++) {
		info->tbufs[i].status = 0;
		info->tbufs[i].count  = 0;
	}
}