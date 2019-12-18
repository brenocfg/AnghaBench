#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fs_context {TYPE_1__* fs_type; TYPE_2__* log; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  usage; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fscontext_alloc_log(struct fs_context *fc)
{
	fc->log = kzalloc(sizeof(*fc->log), GFP_KERNEL);
	if (!fc->log)
		return -ENOMEM;
	refcount_set(&fc->log->usage, 1);
	fc->log->owner = fc->fs_type->owner;
	return 0;
}