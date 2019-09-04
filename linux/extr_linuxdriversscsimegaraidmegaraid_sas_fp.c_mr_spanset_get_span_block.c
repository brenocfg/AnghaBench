#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct fusion_context {TYPE_5__* log_to_span; } ;
struct MR_QUAD_ELEMENT {int /*<<< orphan*/  offsetInSpan; int /*<<< orphan*/  diff; int /*<<< orphan*/  logStart; int /*<<< orphan*/  logEnd; } ;
struct MR_LD_RAID {size_t spanDepth; scalar_t__ stripeShift; } ;
struct TYPE_10__ {TYPE_3__* ldSpanMap; } ;
struct MR_DRV_RAID_MAP_ALL {TYPE_4__ raidMap; } ;
struct TYPE_12__ {scalar_t__ span_row_data_width; scalar_t__ data_row_end; } ;
struct TYPE_11__ {TYPE_6__* span_set; } ;
struct TYPE_9__ {TYPE_2__* spanBlock; } ;
struct TYPE_7__ {struct MR_QUAD_ELEMENT* quad; int /*<<< orphan*/  noElements; } ;
struct TYPE_8__ {TYPE_1__ block_span_info; } ;
typedef  TYPE_5__* PLD_SPAN_INFO ;
typedef  TYPE_6__ LD_SPAN_SET ;

/* Variables and functions */
 size_t MAX_QUAD_DEPTH ; 
 struct MR_LD_RAID* MR_LdRaidGet (size_t,struct MR_DRV_RAID_MAP_ALL*) ; 
 size_t SPAN_INVALID ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mega_div64_32 (scalar_t__,size_t) ; 
 scalar_t__ mega_mod64 (scalar_t__,size_t) ; 

u32 mr_spanset_get_span_block(struct megasas_instance *instance,
		u32 ld, u64 row, u64 *span_blk, struct MR_DRV_RAID_MAP_ALL *map)
{
	struct fusion_context *fusion = instance->ctrl_context;
	struct MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	struct MR_QUAD_ELEMENT    *quad;
	u32    span, info;
	PLD_SPAN_INFO ldSpanInfo = fusion->log_to_span;

	for (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(ldSpanInfo[ld].span_set[info]);

		if (span_set->span_row_data_width == 0)
			break;

		if (row > span_set->data_row_end)
			continue;

		for (span = 0; span < raid->spanDepth; span++)
			if (le32_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements) >= info+1) {
				quad = &map->raidMap.ldSpanMap[ld].
					spanBlock[span].
					block_span_info.quad[info];
				if (le32_to_cpu(quad->diff) == 0)
					return SPAN_INVALID;
				if (le64_to_cpu(quad->logStart) <= row  &&
					row <= le64_to_cpu(quad->logEnd)  &&
					(mega_mod64(row - le64_to_cpu(quad->logStart),
						le32_to_cpu(quad->diff))) == 0) {
					if (span_blk != NULL) {
						u64  blk;
						blk = mega_div64_32
						    ((row - le64_to_cpu(quad->logStart)),
						    le32_to_cpu(quad->diff));
						blk = (blk + le64_to_cpu(quad->offsetInSpan))
							 << raid->stripeShift;
						*span_blk = blk;
					}
					return span;
				}
			}
	}
	return SPAN_INVALID;
}