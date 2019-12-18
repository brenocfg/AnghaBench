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
typedef  scalar_t__ uint32 ;
struct cdb_make {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int cdb_posplus(struct cdb_make *c, uint32 len)
{
	uint32 newpos = c->pos + len;
	if (newpos < len) {
		errno = ENOMEM;
		return -1;
	}
	c->pos = newpos;
	return 0;
}