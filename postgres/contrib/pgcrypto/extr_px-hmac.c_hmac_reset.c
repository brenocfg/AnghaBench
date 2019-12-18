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
struct TYPE_4__ {int /*<<< orphan*/  ipad; } ;
struct TYPE_5__ {TYPE_1__ p; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_2__ PX_HMAC ;

/* Variables and functions */
 unsigned int px_md_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
hmac_reset(PX_HMAC *h)
{
	PX_MD	   *md = h->md;
	unsigned	bs = px_md_block_size(md);

	px_md_reset(md);
	px_md_update(md, h->p.ipad, bs);
}