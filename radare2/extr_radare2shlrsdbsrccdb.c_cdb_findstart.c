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
struct cdb {int fd; scalar_t__ loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cdb_findstart(struct cdb *c) {
	c->loop = 0;
#if !USE_MMAN
	if (c->fd != -1) {
		lseek (c->fd, 0, SEEK_SET);
	}
#endif
}