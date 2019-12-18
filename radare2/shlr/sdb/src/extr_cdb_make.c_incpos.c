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
typedef  scalar_t__ ut32 ;
struct cdb_make {scalar_t__ pos; } ;

/* Variables and functions */

__attribute__((used)) static inline int incpos(struct cdb_make *c, ut32 len) {
	ut32 newpos = c->pos + len;
	if (newpos < len) {
		return 0;
	}
	c->pos = newpos;
	return 1;
}