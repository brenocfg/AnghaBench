#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* print; int /*<<< orphan*/ * block; } ;
struct TYPE_5__ {int cur; int ocur; scalar_t__ cur_enabled; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ isSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_showcursor (TYPE_2__*,int) ; 

__attribute__((used)) static void findPrevWord(RCore *core) {
	int i = core->print->cur_enabled? core->print->cur: 0;
	while (i > 1) {
		if (isSpace (core->block[i])) {
			i--;
		} else if (isSpace (core->block[i - 1])) {
			i -= 2;
		} else {
			break;
		}
	}
	for (; i >= 0; i--) {
		if (isSpace (core->block[i])) {
			if (core->print->cur_enabled) {
				core->print->cur = i + 1;
				core->print->ocur = -1;
				r_core_visual_showcursor (core, true);
			} else {
				// r_core_seek (core, core->offset + i + 1, 1);
			}
			break;
		}
	}
}