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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ time64_t ;
struct afs_call {int /*<<< orphan*/  reply_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 scalar_t__ ktime_divns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static time64_t xdr_decode_expiry(struct afs_call *call, u32 expiry)
{
	return ktime_divns(call->reply_time, NSEC_PER_SEC) + expiry;
}