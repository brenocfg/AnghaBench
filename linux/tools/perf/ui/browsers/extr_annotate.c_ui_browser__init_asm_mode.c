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
struct ui_browser {int /*<<< orphan*/  nr_entries; } ;
struct annotation {int /*<<< orphan*/  nr_asm_entries; } ;

/* Variables and functions */
 struct annotation* browser__annotation (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__reset_index (struct ui_browser*) ; 

__attribute__((used)) static void ui_browser__init_asm_mode(struct ui_browser *browser)
{
	struct annotation *notes = browser__annotation(browser);
	ui_browser__reset_index(browser);
	browser->nr_entries = notes->nr_asm_entries;
}