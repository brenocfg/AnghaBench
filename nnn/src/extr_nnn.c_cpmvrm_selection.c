#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum action { ____Placeholder_action } action ;
struct TYPE_2__ {scalar_t__ filtermode; } ;

/* Variables and functions */
 int FALSE ; 
 int FILTER ; 
 int /*<<< orphan*/  F_CLI ; 
 int MSGWAIT ; 
 size_t OPERATION_FAILED ; 
#define  SEL_CP 130 
#define  SEL_CPMVAS 129 
#define  SEL_MV 128 
 size_t SH_EXEC ; 
 int TRUE ; 
 TYPE_1__ cfg ; 
 int /*<<< orphan*/  clearselection () ; 
 int /*<<< orphan*/  cp ; 
 int /*<<< orphan*/  cpmv_rename (int,char*) ; 
 int /*<<< orphan*/  endselection () ; 
 int /*<<< orphan*/  g_buf ; 
 int get_input (char*) ; 
 int /*<<< orphan*/ * messages ; 
 int /*<<< orphan*/  mv ; 
 int /*<<< orphan*/  opstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printwait (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rmmulstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selsafe () ; 
 int /*<<< orphan*/  spawn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * utils ; 

__attribute__((used)) static bool cpmvrm_selection(enum action sel, char *path, int *presel)
{
	int r;

	endselection();

	if (!selsafe()) {
		*presel = MSGWAIT;
		return FALSE;
	}

	switch (sel) {
	case SEL_CP:
		opstr(g_buf, cp);
		break;
	case SEL_MV:
		opstr(g_buf, mv);
		break;
	case SEL_CPMVAS:
		r = get_input("'c'p / 'm'v as?");
		if (r != 'c' && r != 'm') {
			if (cfg.filtermode)
				*presel = FILTER;
			return FALSE;
		}

		if (!cpmv_rename(r, path)) {
			printwait(messages[OPERATION_FAILED], presel);
			return FALSE;
		}
		break;
	default: /* SEL_RMMUL */
		rmmulstr(g_buf);
		break;
	}

	if (sel != SEL_CPMVAS)
		spawn(utils[SH_EXEC], g_buf, NULL, path, F_CLI);

	/* Clear selection on move or delete */
	if (sel != SEL_CP)
		clearselection();

	if (cfg.filtermode)
		*presel = FILTER;

	return TRUE;
}