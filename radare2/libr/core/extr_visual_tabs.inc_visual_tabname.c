#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {int /*<<< orphan*/  tab; int /*<<< orphan*/  tabs; } ;
struct TYPE_8__ {TYPE_1__ visual; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RCoreVisualTab ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  prompt_read (char*,char*,int) ; 
 TYPE_2__* r_list_get_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void visual_tabname (RCore *core) {
	if (!core->visual.tabs) {
		return;
	}
	char name[32]={0};
	prompt_read ("tab name: ", name, sizeof (name));
	RCoreVisualTab *tab = r_list_get_n (core->visual.tabs, core->visual.tab);
	if (tab) {
		strcpy (tab->name, name);
	}
}