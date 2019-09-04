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
typedef  void* u64 ;
struct recorded_ref {int /*<<< orphan*/  list; void* dir_gen; void* dir; } ;
struct list_head {int dummy; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct recorded_ref* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  set_ref_path (struct recorded_ref*,struct fs_path*) ; 

__attribute__((used)) static int __record_ref(struct list_head *head, u64 dir,
		      u64 dir_gen, struct fs_path *path)
{
	struct recorded_ref *ref;

	ref = kmalloc(sizeof(*ref), GFP_KERNEL);
	if (!ref)
		return -ENOMEM;

	ref->dir = dir;
	ref->dir_gen = dir_gen;
	set_ref_path(ref, path);
	list_add_tail(&ref->list, head);
	return 0;
}