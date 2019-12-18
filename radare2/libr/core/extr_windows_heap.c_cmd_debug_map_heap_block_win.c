#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {struct TYPE_9__* extraInfo; scalar_t__ unusedBytes; scalar_t__ dwSize; int /*<<< orphan*/  dwFlags; scalar_t__ granularity; } ;
struct TYPE_8__ {int /*<<< orphan*/  dbg; int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  RTable ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  PJ ;
typedef  TYPE_2__* PHeapBlock ;

/* Variables and functions */
 TYPE_2__* GetSingleBlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * __new_heapblock_tbl () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 char* get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_msg_block ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_kN (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_println (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_table_add_rowf (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  r_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_table_tostring (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  w32_list_heaps_blocks (TYPE_1__*,char const) ; 

__attribute__((used)) static void cmd_debug_map_heap_block_win(RCore *core, const char *input) {
	char *space = strchr (input, ' ');
	ut64 off = 0;
	PHeapBlock hb = NULL;
	if (space) {
		off = r_num_math (core->num, space + 1);
		PHeapBlock hb = GetSingleBlock (core->dbg, off);
		if (hb) {
			ut64 granularity = hb->extraInfo->granularity;
			char *type = get_type (hb->dwFlags);
			if (!type) {
				type = "";
			}
			PJ *pj = pj_new ();
			RTable *tbl = __new_heapblock_tbl ();
			ut64 headerAddr = off - granularity;
			switch (input[0]) {
			case ' ':
				r_table_add_rowf (tbl, "xxnnns", headerAddr, off, (ut64)hb->dwSize, granularity, (ut64)hb->extraInfo->unusedBytes, type);
				r_cons_println (r_table_tostring (tbl));
				break;
			case 'j':
				pj_o (pj);
				pj_kN (pj, "header_address", headerAddr);
				pj_kN (pj, "user_address", off);
				pj_ks (pj, "type", type);
				pj_kN (pj, "size", hb->dwSize);
				if (hb->extraInfo->unusedBytes) {
					pj_kN (pj, "unused", hb->extraInfo->unusedBytes);
				}
				pj_end (pj);
				r_cons_println (pj_string (pj));
			}
			free (hb->extraInfo);
			free (hb);
			r_table_free (tbl);
			pj_free (pj);
		}
		return;
	}
	switch (input[0]) {
	case '\0':
	case 'f':
	case 'j':
		w32_list_heaps_blocks (core, input[0]);
		break;
	default:
		r_core_cmd_help (core, help_msg_block);
	}
}