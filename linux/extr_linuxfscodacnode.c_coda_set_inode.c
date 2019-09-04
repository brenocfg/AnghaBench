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
struct inode {int dummy; } ;
struct CodaFid {int dummy; } ;
struct coda_inode_info {struct CodaFid c_fid; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 

__attribute__((used)) static int coda_set_inode(struct inode *inode, void *data)
{
	struct CodaFid *fid = (struct CodaFid *)data;
	struct coda_inode_info *cii = ITOC(inode);
	cii->c_fid = *fid;
	return 0;
}