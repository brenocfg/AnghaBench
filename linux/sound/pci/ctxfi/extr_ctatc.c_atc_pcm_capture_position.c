#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct src {TYPE_1__* ops; } ;
struct ct_atc_pcm {TYPE_2__* vm_block; struct src* src; } ;
struct ct_atc {int dummy; } ;
struct TYPE_4__ {int addr; } ;
struct TYPE_3__ {int (* get_ca ) (struct src*) ;} ;

/* Variables and functions */
 int stub1 (struct src*) ; 

__attribute__((used)) static int
atc_pcm_capture_position(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src *src = apcm->src;

	if (!src)
		return 0;
	return src->ops->get_ca(src) - apcm->vm_block->addr;
}