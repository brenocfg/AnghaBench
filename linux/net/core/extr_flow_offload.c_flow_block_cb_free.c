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
struct flow_block_cb {int /*<<< orphan*/  cb_priv; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct flow_block_cb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void flow_block_cb_free(struct flow_block_cb *block_cb)
{
	if (block_cb->release)
		block_cb->release(block_cb->cb_priv);

	kfree(block_cb);
}