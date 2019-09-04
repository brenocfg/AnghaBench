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
struct osd_sg_entry {unsigned int offset; unsigned int len; } ;
struct ore_per_dev_state {int cur_sg; unsigned int offset; unsigned int length; unsigned int last_sgs_total; struct osd_sg_entry* sglist; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORE_DBGMSG (char*,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  _LLU (unsigned int) ; 

void _ore_add_sg_seg(struct ore_per_dev_state *per_dev, unsigned cur_len,
		     bool not_last)
{
	struct osd_sg_entry *sge;

	ORE_DBGMSG("dev=%d cur_len=0x%x not_last=%d cur_sg=%d "
		     "offset=0x%llx length=0x%x last_sgs_total=0x%x\n",
		     per_dev->dev, cur_len, not_last, per_dev->cur_sg,
		     _LLU(per_dev->offset), per_dev->length,
		     per_dev->last_sgs_total);

	if (!per_dev->cur_sg) {
		sge = per_dev->sglist;

		/* First time we prepare two entries */
		if (per_dev->length) {
			++per_dev->cur_sg;
			sge->offset = per_dev->offset;
			sge->len = per_dev->length;
		} else {
			/* Here the parity is the first unit of this object.
			 * This happens every time we reach a parity device on
			 * the same stripe as the per_dev->offset. We need to
			 * just skip this unit.
			 */
			per_dev->offset += cur_len;
			return;
		}
	} else {
		/* finalize the last one */
		sge = &per_dev->sglist[per_dev->cur_sg - 1];
		sge->len = per_dev->length - per_dev->last_sgs_total;
	}

	if (not_last) {
		/* Partly prepare the next one */
		struct osd_sg_entry *next_sge = sge + 1;

		++per_dev->cur_sg;
		next_sge->offset = sge->offset + sge->len + cur_len;
		/* Save cur len so we know how mutch was added next time */
		per_dev->last_sgs_total = per_dev->length;
		next_sge->len = 0;
	} else if (!sge->len) {
		/* Optimize for when the last unit is a parity */
		--per_dev->cur_sg;
	}
}