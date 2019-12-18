#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__* val; } ;
struct fsnotify_mark_connector {unsigned int type; scalar_t__ flags; TYPE_1__ fsid; int /*<<< orphan*/ * obj; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  fsnotify_connp_t ;
typedef  TYPE_1__ __kernel_fsid_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FSNOTIFY_CONN_FLAG_HAS_FSID ; 
 unsigned int FSNOTIFY_OBJ_TYPE_INODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  fsnotify_conn_inode (struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  fsnotify_mark_connector_cachep ; 
 struct inode* igrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct fsnotify_mark_connector* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fsnotify_mark_connector*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsnotify_attach_connector_to_object(fsnotify_connp_t *connp,
					       unsigned int type,
					       __kernel_fsid_t *fsid)
{
	struct inode *inode = NULL;
	struct fsnotify_mark_connector *conn;

	conn = kmem_cache_alloc(fsnotify_mark_connector_cachep, GFP_KERNEL);
	if (!conn)
		return -ENOMEM;
	spin_lock_init(&conn->lock);
	INIT_HLIST_HEAD(&conn->list);
	conn->type = type;
	conn->obj = connp;
	/* Cache fsid of filesystem containing the object */
	if (fsid) {
		conn->fsid = *fsid;
		conn->flags = FSNOTIFY_CONN_FLAG_HAS_FSID;
	} else {
		conn->fsid.val[0] = conn->fsid.val[1] = 0;
		conn->flags = 0;
	}
	if (conn->type == FSNOTIFY_OBJ_TYPE_INODE)
		inode = igrab(fsnotify_conn_inode(conn));
	/*
	 * cmpxchg() provides the barrier so that readers of *connp can see
	 * only initialized structure
	 */
	if (cmpxchg(connp, NULL, conn)) {
		/* Someone else created list structure for us */
		if (inode)
			iput(inode);
		kmem_cache_free(fsnotify_mark_connector_cachep, conn);
	}

	return 0;
}