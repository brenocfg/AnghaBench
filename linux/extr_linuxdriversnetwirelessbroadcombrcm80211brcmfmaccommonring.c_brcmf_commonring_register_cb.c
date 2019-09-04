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
struct brcmf_commonring {int (* cr_ring_bell ) (void*) ;int (* cr_update_rptr ) (void*) ;int (* cr_update_wptr ) (void*) ;int (* cr_write_rptr ) (void*) ;int (* cr_write_wptr ) (void*) ;void* cr_ctx; } ;

/* Variables and functions */

void brcmf_commonring_register_cb(struct brcmf_commonring *commonring,
				  int (*cr_ring_bell)(void *ctx),
				  int (*cr_update_rptr)(void *ctx),
				  int (*cr_update_wptr)(void *ctx),
				  int (*cr_write_rptr)(void *ctx),
				  int (*cr_write_wptr)(void *ctx), void *ctx)
{
	commonring->cr_ring_bell = cr_ring_bell;
	commonring->cr_update_rptr = cr_update_rptr;
	commonring->cr_update_wptr = cr_update_wptr;
	commonring->cr_write_rptr = cr_write_rptr;
	commonring->cr_write_wptr = cr_write_wptr;
	commonring->cr_ctx = ctx;
}