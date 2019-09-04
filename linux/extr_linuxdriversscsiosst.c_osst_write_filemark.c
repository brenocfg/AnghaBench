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
struct osst_tape {int first_frame_position; int logical_blk_num; int dirty; int last_mark_ppos; int last_mark_lbn; size_t filemark_cnt; int first_mark_ppos; TYPE_2__* header_cache; int /*<<< orphan*/  write_type; scalar_t__ raw; } ;
struct osst_request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fm_tab_ent; } ;
struct TYPE_4__ {TYPE_1__ dat_fm_tab; } ;

/* Variables and functions */
 size_t OS_FM_TAB_MAX ; 
 int /*<<< orphan*/  OS_WRITE_NEW_MARK ; 
 int /*<<< orphan*/  htonl (int) ; 
 int osst_flush_drive_buffer (struct osst_tape*,struct osst_request**) ; 
 int osst_flush_write_buffer (struct osst_tape*,struct osst_request**) ; 

__attribute__((used)) static int osst_write_filemark(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	result;
	int	this_mark_ppos = STp->first_frame_position;
	int	this_mark_lbn  = STp->logical_blk_num;
#if DEBUG
	char  * name = tape_name(STp);
#endif

	if (STp->raw) return 0;

	STp->write_type = OS_WRITE_NEW_MARK;
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Writing Filemark %i at fppos %d (fseq %d, lblk %d)\n", 
	       name, STp->filemark_cnt, this_mark_ppos, STp->frame_seq_number, this_mark_lbn);
#endif
	STp->dirty = 1;
	result  = osst_flush_write_buffer(STp, aSRpnt);
	result |= osst_flush_drive_buffer(STp, aSRpnt);
	STp->last_mark_ppos = this_mark_ppos;
	STp->last_mark_lbn  = this_mark_lbn;
	if (STp->header_cache != NULL && STp->filemark_cnt < OS_FM_TAB_MAX)
		STp->header_cache->dat_fm_tab.fm_tab_ent[STp->filemark_cnt] = htonl(this_mark_ppos);
	if (STp->filemark_cnt++ == 0)
		STp->first_mark_ppos = this_mark_ppos;
	return result;
}