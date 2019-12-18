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
typedef  int u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  NFS4_CDFC4_BACK 131 
#define  NFS4_CDFC4_BACK_OR_BOTH 130 
 int NFS4_CDFC4_BOTH ; 
#define  NFS4_CDFC4_FORE 129 
#define  NFS4_CDFC4_FORE_OR_BOTH 128 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32 nfsd4_map_bcts_dir(u32 *dir)
{
	switch (*dir) {
	case NFS4_CDFC4_FORE:
	case NFS4_CDFC4_BACK:
		return nfs_ok;
	case NFS4_CDFC4_FORE_OR_BOTH:
	case NFS4_CDFC4_BACK_OR_BOTH:
		*dir = NFS4_CDFC4_BOTH;
		return nfs_ok;
	};
	return nfserr_inval;
}