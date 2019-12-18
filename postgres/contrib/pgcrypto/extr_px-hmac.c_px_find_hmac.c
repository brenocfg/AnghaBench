#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* opad; void* ipad; } ;
struct TYPE_5__ {int /*<<< orphan*/  init; int /*<<< orphan*/  free; int /*<<< orphan*/  finish; int /*<<< orphan*/  update; int /*<<< orphan*/  reset; int /*<<< orphan*/  block_size; int /*<<< orphan*/  result_size; int /*<<< orphan*/ * md; TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_2__ PX_HMAC ;

/* Variables and functions */
 int PXE_HASH_UNUSABLE_FOR_HMAC ; 
 int /*<<< orphan*/  hmac_block_size ; 
 int /*<<< orphan*/  hmac_finish ; 
 int /*<<< orphan*/  hmac_free ; 
 int /*<<< orphan*/  hmac_init ; 
 int /*<<< orphan*/  hmac_reset ; 
 int /*<<< orphan*/  hmac_result_size ; 
 int /*<<< orphan*/  hmac_update ; 
 void* px_alloc (unsigned int) ; 
 int px_find_digest (char const*,int /*<<< orphan*/ **) ; 
 unsigned int px_md_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_free (int /*<<< orphan*/ *) ; 

int
px_find_hmac(const char *name, PX_HMAC **res)
{
	int			err;
	PX_MD	   *md;
	PX_HMAC    *h;
	unsigned	bs;

	err = px_find_digest(name, &md);
	if (err)
		return err;

	bs = px_md_block_size(md);
	if (bs < 2)
	{
		px_md_free(md);
		return PXE_HASH_UNUSABLE_FOR_HMAC;
	}

	h = px_alloc(sizeof(*h));
	h->p.ipad = px_alloc(bs);
	h->p.opad = px_alloc(bs);
	h->md = md;

	h->result_size = hmac_result_size;
	h->block_size = hmac_block_size;
	h->reset = hmac_reset;
	h->update = hmac_update;
	h->finish = hmac_finish;
	h->free = hmac_free;
	h->init = hmac_init;

	*res = h;

	return 0;
}