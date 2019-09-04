#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int msr; } ;
struct src {int multi; TYPE_3__ rsc; TYPE_1__* ops; } ;
struct ct_atc_pcm {TYPE_4__* vm_block; struct src* src; } ;
struct ct_atc {TYPE_2__* card; } ;
struct TYPE_8__ {int addr; int size; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int (* get_ca ) (struct src*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int stub1 (struct src*) ; 

__attribute__((used)) static int
atc_pcm_playback_position(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct src *src = apcm->src;
	u32 size, max_cisz;
	int position;

	if (!src)
		return 0;
	position = src->ops->get_ca(src);

	if (position < apcm->vm_block->addr) {
		dev_dbg(atc->card->dev,
			"bad ca - ca=0x%08x, vba=0x%08x, vbs=0x%08x\n",
			position, apcm->vm_block->addr, apcm->vm_block->size);
		position = apcm->vm_block->addr;
	}

	size = apcm->vm_block->size;
	max_cisz = src->multi * src->rsc.msr;
	max_cisz = 128 * (max_cisz < 8 ? max_cisz : 8);

	return (position + size - max_cisz - apcm->vm_block->addr) % size;
}