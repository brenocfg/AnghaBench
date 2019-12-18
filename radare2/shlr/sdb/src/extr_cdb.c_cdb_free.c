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
struct cdb {int /*<<< orphan*/ * map; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cdb_free(struct cdb *c) {
	if (!c->map) {
		return;
	}
#if USE_MMAN
	(void)munmap (c->map, c->size);
#else
	free (c->map);
#endif
	c->map = NULL;
}