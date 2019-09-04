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
struct xt_sctp_info {int flags; int invflags; int chunk_match_type; } ;
struct xt_mtchk_param {struct xt_sctp_info* matchinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int SCTP_CHUNK_MATCH_ALL ; 
 int SCTP_CHUNK_MATCH_ANY ; 
 int SCTP_CHUNK_MATCH_ONLY ; 
 int XT_SCTP_CHUNK_TYPES ; 
 int XT_SCTP_VALID_FLAGS ; 

__attribute__((used)) static int sctp_mt_check(const struct xt_mtchk_param *par)
{
	const struct xt_sctp_info *info = par->matchinfo;

	if (info->flags & ~XT_SCTP_VALID_FLAGS)
		return -EINVAL;
	if (info->invflags & ~XT_SCTP_VALID_FLAGS)
		return -EINVAL;
	if (info->invflags & ~info->flags)
		return -EINVAL;
	if (!(info->flags & XT_SCTP_CHUNK_TYPES))
		return 0;
	if (info->chunk_match_type & (SCTP_CHUNK_MATCH_ALL |
	    SCTP_CHUNK_MATCH_ANY | SCTP_CHUNK_MATCH_ONLY))
		return 0;
	return -EINVAL;
}