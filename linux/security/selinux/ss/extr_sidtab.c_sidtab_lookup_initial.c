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
typedef  int u32 ;
struct sidtab {TYPE_1__* isids; } ;
struct context {int dummy; } ;
struct TYPE_2__ {struct context context; scalar_t__ set; } ;

/* Variables and functions */

__attribute__((used)) static struct context *sidtab_lookup_initial(struct sidtab *s, u32 sid)
{
	return s->isids[sid - 1].set ? &s->isids[sid - 1].context : NULL;
}