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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
typedef  int u32 ;
struct udf_sparing_data {int s_packet_len; TYPE_2__** s_spar_map; } ;
struct udf_sb_info {struct udf_part_map* s_partmaps; } ;
struct TYPE_3__ {struct udf_sparing_data s_sparing; } ;
struct udf_part_map {int s_partition_root; TYPE_1__ s_type_specific; } ;
struct super_block {int dummy; } ;
struct sparingTable {struct sparingEntry* mapEntry; int /*<<< orphan*/  reallocationTableLen; } ;
struct sparingEntry {int /*<<< orphan*/  mappedLocation; int /*<<< orphan*/  origLocation; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

uint32_t udf_get_pblock_spar15(struct super_block *sb, uint32_t block,
			       uint16_t partition, uint32_t offset)
{
	int i;
	struct sparingTable *st = NULL;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map;
	uint32_t packet;
	struct udf_sparing_data *sdata;

	map = &sbi->s_partmaps[partition];
	sdata = &map->s_type_specific.s_sparing;
	packet = (block + offset) & ~(sdata->s_packet_len - 1);

	for (i = 0; i < 4; i++) {
		if (sdata->s_spar_map[i] != NULL) {
			st = (struct sparingTable *)
					sdata->s_spar_map[i]->b_data;
			break;
		}
	}

	if (st) {
		for (i = 0; i < le16_to_cpu(st->reallocationTableLen); i++) {
			struct sparingEntry *entry = &st->mapEntry[i];
			u32 origLoc = le32_to_cpu(entry->origLocation);
			if (origLoc >= 0xFFFFFFF0)
				break;
			else if (origLoc == packet)
				return le32_to_cpu(entry->mappedLocation) +
					((block + offset) &
						(sdata->s_packet_len - 1));
			else if (origLoc > packet)
				break;
		}
	}

	return map->s_partition_root + block + offset;
}