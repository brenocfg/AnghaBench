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
typedef  void* u16 ;
struct brcmf_commonring {int inited; scalar_t__ f_ptr; int /*<<< orphan*/  cr_ctx; int /*<<< orphan*/  (* cr_write_wptr ) (int /*<<< orphan*/ ) ;scalar_t__ w_ptr; int /*<<< orphan*/  (* cr_write_rptr ) (int /*<<< orphan*/ ) ;scalar_t__ r_ptr; int /*<<< orphan*/  lock; void* buf_addr; void* item_len; void* depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void brcmf_commonring_config(struct brcmf_commonring *commonring, u16 depth,
			     u16 item_len, void *buf_addr)
{
	commonring->depth = depth;
	commonring->item_len = item_len;
	commonring->buf_addr = buf_addr;
	if (!commonring->inited) {
		spin_lock_init(&commonring->lock);
		commonring->inited = true;
	}
	commonring->r_ptr = 0;
	if (commonring->cr_write_rptr)
		commonring->cr_write_rptr(commonring->cr_ctx);
	commonring->w_ptr = 0;
	if (commonring->cr_write_wptr)
		commonring->cr_write_wptr(commonring->cr_ctx);
	commonring->f_ptr = 0;
}