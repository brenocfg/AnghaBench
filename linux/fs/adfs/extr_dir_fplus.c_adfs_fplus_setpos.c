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
struct adfs_dir {unsigned int pos; TYPE_1__** bh_fplus; } ;
struct adfs_bigdirheader {int /*<<< orphan*/  bigdirentries; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOENT ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
adfs_fplus_setpos(struct adfs_dir *dir, unsigned int fpos)
{
	struct adfs_bigdirheader *h =
		(struct adfs_bigdirheader *) dir->bh_fplus[0]->b_data;
	int ret = -ENOENT;

	if (fpos <= le32_to_cpu(h->bigdirentries)) {
		dir->pos = fpos;
		ret = 0;
	}

	return ret;
}