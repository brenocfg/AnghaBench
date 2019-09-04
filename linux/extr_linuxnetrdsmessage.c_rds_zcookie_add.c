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
typedef  int /*<<< orphan*/  u32 ;
struct rds_zcopy_cookies {int num; int /*<<< orphan*/ * cookies; } ;
struct rds_msg_zcopy_info {struct rds_zcopy_cookies zcookies; } ;

/* Variables and functions */
 int RDS_MAX_ZCOOKIES ; 

__attribute__((used)) static inline bool rds_zcookie_add(struct rds_msg_zcopy_info *info, u32 cookie)
{
	struct rds_zcopy_cookies *ck = &info->zcookies;
	int ncookies = ck->num;

	if (ncookies == RDS_MAX_ZCOOKIES)
		return false;
	ck->cookies[ncookies] = cookie;
	ck->num =  ++ncookies;
	return true;
}