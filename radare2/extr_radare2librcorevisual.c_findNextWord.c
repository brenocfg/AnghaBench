#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int blocksize; int* block; int /*<<< orphan*/  offset; TYPE_1__* print; } ;
struct TYPE_6__ {int cur; int ocur; scalar_t__ cur_enabled; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_seek (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_visual_showcursor (TYPE_2__*,int) ; 

__attribute__((used)) static void findNextWord(RCore *core) {
	int i, d = core->print->cur_enabled? core->print->cur: 0;
	for (i = d + 1; i < core->blocksize; i++) {
		switch (core->block[i]) {
		case ' ':
		case '.':
		case '\t':
		case '\n':
			if (core->print->cur_enabled) {
				core->print->cur = i + 1;
				core->print->ocur = -1;
				r_core_visual_showcursor (core, true);
			} else {
				r_core_seek (core, core->offset + i + 1, 1);
			}
			return;
		}
	}
}