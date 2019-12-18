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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int /*<<< orphan*/ * opad; } ;
struct TYPE_5__ {TYPE_1__ p; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_2__ PX_HMAC ;

/* Variables and functions */
 int /*<<< orphan*/ * px_alloc (unsigned int) ; 
 int /*<<< orphan*/  px_free (int /*<<< orphan*/ *) ; 
 unsigned int px_md_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_reset (int /*<<< orphan*/ *) ; 
 unsigned int px_md_result_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
hmac_finish(PX_HMAC *h, uint8 *dst)
{
	PX_MD	   *md = h->md;
	unsigned	bs,
				hlen;
	uint8	   *buf;

	bs = px_md_block_size(md);
	hlen = px_md_result_size(md);

	buf = px_alloc(hlen);

	px_md_finish(md, buf);

	px_md_reset(md);
	px_md_update(md, h->p.opad, bs);
	px_md_update(md, buf, hlen);
	px_md_finish(md, dst);

	px_memset(buf, 0, hlen);
	px_free(buf);
}