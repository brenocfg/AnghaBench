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
struct page {int dummy; } ;
struct key {int dummy; } ;
struct afs_vnode {int /*<<< orphan*/  flags; } ;
struct afs_read {unsigned int len; int nr_pages; struct page** pages; struct page** array; scalar_t__ pos; int /*<<< orphan*/  usage; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ESTALE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*,unsigned long long) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int afs_fetch_data (struct afs_vnode*,struct key*,struct afs_read*) ; 
 int /*<<< orphan*/  afs_put_read (struct afs_read*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct afs_read* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_fill_page(struct afs_vnode *vnode, struct key *key,
			 loff_t pos, unsigned int len, struct page *page)
{
	struct afs_read *req;
	int ret;

	_enter(",,%llu", (unsigned long long)pos);

	req = kzalloc(sizeof(struct afs_read) + sizeof(struct page *),
		      GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	refcount_set(&req->usage, 1);
	req->pos = pos;
	req->len = len;
	req->nr_pages = 1;
	req->pages = req->array;
	req->pages[0] = page;
	get_page(page);

	ret = afs_fetch_data(vnode, key, req);
	afs_put_read(req);
	if (ret < 0) {
		if (ret == -ENOENT) {
			_debug("got NOENT from server"
			       " - marking file deleted and stale");
			set_bit(AFS_VNODE_DELETED, &vnode->flags);
			ret = -ESTALE;
		}
	}

	_leave(" = %d", ret);
	return ret;
}