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
struct TYPE_9__ {TYPE_1__* panels; } ;
struct TYPE_8__ {size_t curnode; int /*<<< orphan*/ * panel; } ;
typedef  TYPE_1__ RPanels ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  handleTabKey (TYPE_2__*,int) ; 
 int /*<<< orphan*/  maximizePanelSize (TYPE_1__*) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 int /*<<< orphan*/  restorePanelPos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savePanelPos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggleHelp (TYPE_2__*) ; 
 int /*<<< orphan*/  toggleZoomMode (TYPE_1__*) ; 

__attribute__((used)) static bool handleZoomMode(RCore *core, const int key) {
	RPanels *panels = core->panels;
	r_cons_switchbuf (false);
	switch (key) {
	case 'Q':
	case 'q':
	case 0x0d:
		toggleZoomMode (panels);
		break;
	case 'c':
	case 'C':
	case ';':
	case ' ':
	case 'b':
	case 'd':
	case 'n':
	case 'N':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'l':
	case 'p':
	case 'P':
	case 's':
	case 'S':
	case 't':
	case 'T':
	case 'x':
	case 'X':
	case ':':
		return false;
	case 9:
		restorePanelPos (panels->panel[panels->curnode]);
		handleTabKey (core, false);
		savePanelPos (panels->panel[panels->curnode]);
		maximizePanelSize (panels);
		break;
	case 'Z':
		restorePanelPos (panels->panel[panels->curnode]);
		handleTabKey (core, true);
		savePanelPos (panels->panel[panels->curnode]);
		maximizePanelSize (panels);
		break;
	case '?':
		toggleZoomMode (panels);
		toggleHelp (core);
		toggleZoomMode (panels);
		break;
	}
	return true;
}