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
struct snd_seq_port_subscribe {scalar_t__ flags; scalar_t__ queue; int /*<<< orphan*/  dest; int /*<<< orphan*/  sender; } ;

/* Variables and functions */
 scalar_t__ addr_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int match_subs_info(struct snd_seq_port_subscribe *r,
			   struct snd_seq_port_subscribe *s)
{
	if (addr_match(&r->sender, &s->sender) &&
	    addr_match(&r->dest, &s->dest)) {
		if (r->flags && r->flags == s->flags)
			return r->queue == s->queue;
		else if (! r->flags)
			return 1;
	}
	return 0;
}