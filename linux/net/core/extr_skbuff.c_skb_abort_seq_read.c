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
struct skb_seq_state {scalar_t__ frag_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap_atomic (scalar_t__) ; 

void skb_abort_seq_read(struct skb_seq_state *st)
{
	if (st->frag_data)
		kunmap_atomic(st->frag_data);
}