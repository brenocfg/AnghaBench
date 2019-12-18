#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int count; int /*<<< orphan*/  payload; } ;
struct TYPE_4__ {int* mask; int /*<<< orphan*/ ** val; } ;
struct TYPE_5__ {TYPE_1__ items; } ;
struct intel_pt_decoder {int blk_type_pos; TYPE_3__ packet; TYPE_2__ state; int /*<<< orphan*/  blk_type; } ;

/* Variables and functions */
 int INTEL_PT_BLK_ITEM_ID_CNT ; 
 int /*<<< orphan*/  intel_pt_log (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pt_bip(struct intel_pt_decoder *decoder)
{
	uint32_t id = decoder->packet.count;
	uint32_t bit = 1 << id;
	int pos = decoder->blk_type_pos;

	if (pos < 0 || id >= INTEL_PT_BLK_ITEM_ID_CNT) {
		intel_pt_log("WARNING: Unknown block item %u type %d\n",
			     id, decoder->blk_type);
		return;
	}

	if (decoder->state.items.mask[pos] & bit) {
		intel_pt_log("WARNING: Duplicate block item %u type %d\n",
			     id, decoder->blk_type);
	}

	decoder->state.items.mask[pos] |= bit;
	decoder->state.items.val[pos][id] = decoder->packet.payload;
}