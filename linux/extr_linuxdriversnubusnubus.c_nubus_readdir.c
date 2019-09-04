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
typedef  int u32 ;
struct nubus_dirent {int type; int data; int /*<<< orphan*/  mask; int /*<<< orphan*/  base; } ;
struct nubus_dir {int done; int /*<<< orphan*/  mask; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int nubus_get_rom (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int nubus_readdir(struct nubus_dir *nd, struct nubus_dirent *ent)
{
	u32 resid;

	if (nd->done)
		return -1;

	/* Do this first, otherwise nubus_rewind & co are off by 4 */
	ent->base = nd->ptr;

	/* This moves nd->ptr forward */
	resid = nubus_get_rom(&nd->ptr, 4, nd->mask);

	/* EOL marker, as per the Apple docs */
	if ((resid & 0xff000000) == 0xff000000) {
		/* Mark it as done */
		nd->done = 1;
		return -1;
	}

	/* First byte is the resource ID */
	ent->type = resid >> 24;
	/* Low 3 bytes might contain data (or might not) */
	ent->data = resid & 0xffffff;
	ent->mask = nd->mask;
	return 0;
}