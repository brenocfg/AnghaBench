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
struct tcf_block_cb {void* cb_priv; } ;

/* Variables and functions */

void *tcf_block_cb_priv(struct tcf_block_cb *block_cb)
{
	return block_cb->cb_priv;
}