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
struct fuse_req {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_req_cachep ; 
 int /*<<< orphan*/  fuse_request_init (struct fuse_req*) ; 
 struct fuse_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fuse_req *fuse_request_alloc(gfp_t flags)
{
	struct fuse_req *req = kmem_cache_zalloc(fuse_req_cachep, flags);
	if (req)
		fuse_request_init(req);

	return req;
}