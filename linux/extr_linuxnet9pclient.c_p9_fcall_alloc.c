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
struct p9_fcall {int capacity; char* sdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct p9_fcall* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct p9_fcall *p9_fcall_alloc(int alloc_msize)
{
	struct p9_fcall *fc;
	fc = kmalloc(sizeof(struct p9_fcall) + alloc_msize, GFP_NOFS);
	if (!fc)
		return NULL;
	fc->capacity = alloc_msize;
	fc->sdata = (char *) fc + sizeof(struct p9_fcall);
	return fc;
}