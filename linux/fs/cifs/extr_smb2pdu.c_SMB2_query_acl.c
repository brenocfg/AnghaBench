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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct cifs_tcon {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int DACL_SECINFO ; 
 int GROUP_SECINFO ; 
 int /*<<< orphan*/  MIN_SEC_DESC_LEN ; 
 int OWNER_SECINFO ; 
 int /*<<< orphan*/  SMB2_MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  SMB2_O_INFO_SECURITY ; 
 int query_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,scalar_t__*) ; 

int
SMB2_query_acl(const unsigned int xid, struct cifs_tcon *tcon,
		u64 persistent_fid, u64 volatile_fid,
		void **data, u32 *plen)
{
	__u32 additional_info = OWNER_SECINFO | GROUP_SECINFO | DACL_SECINFO;
	*plen = 0;

	return query_info(xid, tcon, persistent_fid, volatile_fid,
			  0, SMB2_O_INFO_SECURITY, additional_info,
			  SMB2_MAX_BUFFER_SIZE, MIN_SEC_DESC_LEN, data, plen);
}