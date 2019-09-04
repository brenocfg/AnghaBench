#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int cost; int credit; scalar_t__ credit_cap; } ;
struct dsthash_ent {TYPE_1__ rateinfo; } ;

/* Variables and functions */
 int CREDITS_PER_JIFFY_BYTES ; 
 int HZ ; 
 scalar_t__ unlikely (int) ; 
 int xt_hashlimit_len_to_chunks (unsigned int) ; 

__attribute__((used)) static u32 hashlimit_byte_cost(unsigned int len, struct dsthash_ent *dh)
{
	u64 tmp = xt_hashlimit_len_to_chunks(len);
	tmp = tmp * dh->rateinfo.cost;

	if (unlikely(tmp > CREDITS_PER_JIFFY_BYTES * HZ))
		tmp = CREDITS_PER_JIFFY_BYTES * HZ;

	if (dh->rateinfo.credit < tmp && dh->rateinfo.credit_cap) {
		dh->rateinfo.credit_cap--;
		dh->rateinfo.credit = CREDITS_PER_JIFFY_BYTES * HZ;
	}
	return (u32) tmp;
}