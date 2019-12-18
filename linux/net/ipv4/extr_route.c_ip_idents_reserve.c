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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int IP_IDENTS_SZ ; 
 int READ_ONCE (int) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/ * ip_idents ; 
 int* ip_tstamps ; 
 scalar_t__ jiffies ; 
 int prandom_u32_max (int) ; 

u32 ip_idents_reserve(u32 hash, int segs)
{
	u32 *p_tstamp = ip_tstamps + hash % IP_IDENTS_SZ;
	atomic_t *p_id = ip_idents + hash % IP_IDENTS_SZ;
	u32 old = READ_ONCE(*p_tstamp);
	u32 now = (u32)jiffies;
	u32 new, delta = 0;

	if (old != now && cmpxchg(p_tstamp, old, now) == old)
		delta = prandom_u32_max(now - old);

	/* Do not use atomic_add_return() as it makes UBSAN unhappy */
	do {
		old = (u32)atomic_read(p_id);
		new = old + delta + segs;
	} while (atomic_cmpxchg(p_id, old, new) != old);

	return new - segs;
}