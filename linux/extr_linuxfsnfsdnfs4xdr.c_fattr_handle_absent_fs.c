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
 int FATTR4_WORD0_FS_LOCATIONS ; 
 int FATTR4_WORD0_RDATTR_ERROR ; 
 int NFSERR_MOVED ; 
 int WORD0_ABSENT_FS_ATTRS ; 
 int WORD1_ABSENT_FS_ATTRS ; 
 int WORD2_ABSENT_FS_ATTRS ; 
 int /*<<< orphan*/  nfserr_moved ; 

__attribute__((used)) static __be32 fattr_handle_absent_fs(u32 *bmval0, u32 *bmval1, u32 *bmval2, u32 *rdattr_err)
{
	/* As per referral draft:  */
	if (*bmval0 & ~WORD0_ABSENT_FS_ATTRS ||
	    *bmval1 & ~WORD1_ABSENT_FS_ATTRS) {
		if (*bmval0 & FATTR4_WORD0_RDATTR_ERROR ||
	            *bmval0 & FATTR4_WORD0_FS_LOCATIONS)
			*rdattr_err = NFSERR_MOVED;
		else
			return nfserr_moved;
	}
	*bmval0 &= WORD0_ABSENT_FS_ATTRS;
	*bmval1 &= WORD1_ABSENT_FS_ATTRS;
	*bmval2 &= WORD2_ABSENT_FS_ATTRS;
	return 0;
}