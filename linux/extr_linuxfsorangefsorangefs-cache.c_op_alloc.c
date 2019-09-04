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
struct TYPE_4__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; void* type; } ;
struct TYPE_3__ {int status; void* type; } ;
struct orangefs_kernel_op_s {TYPE_2__ upcall; int /*<<< orphan*/  tag; scalar_t__ attempts; int /*<<< orphan*/  op_state; TYPE_1__ downcall; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
typedef  void* __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOSSIP_CACHE_DEBUG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP_VFS_STATE_UNKNOWN ; 
 void* ORANGEFS_VFS_OP_INVALID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opname_string (struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,struct orangefs_kernel_op_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gossip_err (char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct orangefs_kernel_op_s* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_cache ; 
 int /*<<< orphan*/  orangefs_new_tag (struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct orangefs_kernel_op_s *op_alloc(__s32 type)
{
	struct orangefs_kernel_op_s *new_op = NULL;

	new_op = kmem_cache_zalloc(op_cache, GFP_KERNEL);
	if (new_op) {
		INIT_LIST_HEAD(&new_op->list);
		spin_lock_init(&new_op->lock);
		init_completion(&new_op->waitq);

		new_op->upcall.type = ORANGEFS_VFS_OP_INVALID;
		new_op->downcall.type = ORANGEFS_VFS_OP_INVALID;
		new_op->downcall.status = -1;

		new_op->op_state = OP_VFS_STATE_UNKNOWN;

		/* initialize the op specific tag and upcall credentials */
		orangefs_new_tag(new_op);
		new_op->upcall.type = type;
		new_op->attempts = 0;
		gossip_debug(GOSSIP_CACHE_DEBUG,
			     "Alloced OP (%p: %llu %s)\n",
			     new_op,
			     llu(new_op->tag),
			     get_opname_string(new_op));

		new_op->upcall.uid = from_kuid(&init_user_ns,
					       current_fsuid());

		new_op->upcall.gid = from_kgid(&init_user_ns,
					       current_fsgid());
	} else {
		gossip_err("op_alloc: kmem_cache_zalloc failed!\n");
	}
	return new_op;
}