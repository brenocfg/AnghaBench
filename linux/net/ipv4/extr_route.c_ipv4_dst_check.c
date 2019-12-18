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
struct rtable {int dummy; } ;
struct dst_entry {scalar_t__ obsolete; } ;

/* Variables and functions */
 scalar_t__ DST_OBSOLETE_FORCE_CHK ; 
 scalar_t__ rt_is_expired (struct rtable*) ; 

__attribute__((used)) static struct dst_entry *ipv4_dst_check(struct dst_entry *dst, u32 cookie)
{
	struct rtable *rt = (struct rtable *) dst;

	/* All IPV4 dsts are created with ->obsolete set to the value
	 * DST_OBSOLETE_FORCE_CHK which forces validation calls down
	 * into this function always.
	 *
	 * When a PMTU/redirect information update invalidates a route,
	 * this is indicated by setting obsolete to DST_OBSOLETE_KILL or
	 * DST_OBSOLETE_DEAD.
	 */
	if (dst->obsolete != DST_OBSOLETE_FORCE_CHK || rt_is_expired(rt))
		return NULL;
	return dst;
}