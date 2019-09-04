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
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 struct fuse_req* __fuse_get_req (struct fuse_conn*,unsigned int,int) ; 

struct fuse_req *fuse_get_req_for_background(struct fuse_conn *fc,
					     unsigned npages)
{
	return __fuse_get_req(fc, npages, true);
}