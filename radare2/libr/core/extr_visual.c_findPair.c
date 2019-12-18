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
typedef  char ut8 ;
struct TYPE_6__ {char* block; TYPE_1__* print; scalar_t__ blocksize; } ;
struct TYPE_5__ {int cur; int ocur; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ R_MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  r_core_visual_showcursor (TYPE_2__*,int) ; 
 char* r_mem_mem (char*,scalar_t__,char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static void findPair(RCore *core) {
	ut8 buf[256];
	int i, len, d = core->print->cur + 1;
	int delta = 0;
	const ut8 *p, *q = NULL;
	const char *keys = "{}[]()<>";
	ut8 ch = core->block[core->print->cur];

	p = (const ut8 *) strchr (keys, ch);
	if (p) {
		char p_1 = 0;
		if ((const char *) p > keys) {
			p_1 = p[-1];
		}
		delta = (size_t) (p - (const ut8 *) keys);
		ch = (delta % 2 && p != (const ut8 *) keys)? p_1: p[1];
	}
	len = 1;
	buf[0] = ch;

	if (p && (delta % 2)) {
		for (i = d - 1; i >= 0; i--) {
			if (core->block[i] == ch) {
				q = core->block + i;
				break;
			}
		}
	} else {
		q = r_mem_mem (core->block + d, core->blocksize - d,
			(const ut8 *) buf, len);
		if (!q) {
			q = r_mem_mem (core->block, R_MIN (core->blocksize, d),
				(const ut8 *) buf, len);
		}
	}
	if (q) {
		core->print->cur = (int) (size_t) (q - core->block);
		core->print->ocur = -1;
		r_core_visual_showcursor (core, true);
	}
}