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
struct TYPE_2__ {scalar_t__ dircolor; scalar_t__ curctx; } ;

/* Variables and functions */
 int A_BOLD ; 
 int COLOR_PAIR (scalar_t__) ; 
 int DIR_OR_LINK_TO_DIR ; 
 int /*<<< orphan*/  attroff (int) ; 
 TYPE_1__ cfg ; 

__attribute__((used)) static inline void resetdircolor(int flags)
{
	if (cfg.dircolor && !(flags & DIR_OR_LINK_TO_DIR)) {
		attroff(COLOR_PAIR(cfg.curctx + 1) | A_BOLD);
		cfg.dircolor = 0;
	}
}