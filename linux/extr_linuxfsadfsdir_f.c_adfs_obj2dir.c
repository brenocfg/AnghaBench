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
struct object_info {int /*<<< orphan*/  attr; int /*<<< orphan*/  size; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  file_id; } ;
struct adfs_direntry {int /*<<< orphan*/  newdiratts; int /*<<< orphan*/  dirlen; int /*<<< orphan*/  direxec; int /*<<< orphan*/  dirload; int /*<<< orphan*/  dirinddiscadd; } ;

/* Variables and functions */
 int /*<<< orphan*/  adfs_writeval (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
adfs_obj2dir(struct adfs_direntry *de, struct object_info *obj)
{
	adfs_writeval(de->dirinddiscadd, 3, obj->file_id);
	adfs_writeval(de->dirload, 4, obj->loadaddr);
	adfs_writeval(de->direxec, 4, obj->execaddr);
	adfs_writeval(de->dirlen,  4, obj->size);
	de->newdiratts = obj->attr;
}