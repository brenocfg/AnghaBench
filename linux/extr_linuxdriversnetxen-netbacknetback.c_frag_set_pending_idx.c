#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  page_offset; } ;
typedef  TYPE_1__ skb_frag_t ;

/* Variables and functions */

__attribute__((used)) static void frag_set_pending_idx(skb_frag_t *frag, u16 pending_idx)
{
	frag->page_offset = pending_idx;
}