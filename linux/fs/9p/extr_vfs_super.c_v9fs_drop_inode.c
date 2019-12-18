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
struct v9fs_session_info {scalar_t__ cache; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ CACHE_FSCACHE ; 
 scalar_t__ CACHE_LOOSE ; 
 int generic_drop_inode (struct inode*) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 

__attribute__((used)) static int v9fs_drop_inode(struct inode *inode)
{
	struct v9fs_session_info *v9ses;
	v9ses = v9fs_inode2v9ses(inode);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE)
		return generic_drop_inode(inode);
	/*
	 * in case of non cached mode always drop the
	 * the inode because we want the inode attribute
	 * to always match that on the server.
	 */
	return 1;
}