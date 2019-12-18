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
struct ip_set_ext {int /*<<< orphan*/  bytes_op; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets_op; int /*<<< orphan*/  packets; } ;
struct ip_set_counter {int dummy; } ;
struct ip_set {int dummy; } ;

/* Variables and functions */
 int IPSET_FLAG_MATCH_COUNTERS ; 
 scalar_t__ SET_WITH_COUNTER (struct ip_set*) ; 
 scalar_t__ SET_WITH_SKBINFO (struct ip_set*) ; 
 scalar_t__ SET_WITH_TIMEOUT (struct ip_set*) ; 
 struct ip_set_counter* ext_counter (void*,struct ip_set*) ; 
 int /*<<< orphan*/  ext_skbinfo (void*,struct ip_set*) ; 
 int /*<<< orphan*/  ext_timeout (void*,struct ip_set*) ; 
 int /*<<< orphan*/  ip_set_get_bytes (struct ip_set_counter*) ; 
 int /*<<< orphan*/  ip_set_get_packets (struct ip_set_counter*) ; 
 int /*<<< orphan*/  ip_set_get_skbinfo (int /*<<< orphan*/ ,struct ip_set_ext const*,struct ip_set_ext*,int) ; 
 scalar_t__ ip_set_match_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ip_set_timeout_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_update_counter (struct ip_set_counter*,struct ip_set_ext const*,int) ; 

bool
ip_set_match_extensions(struct ip_set *set, const struct ip_set_ext *ext,
			struct ip_set_ext *mext, u32 flags, void *data)
{
	if (SET_WITH_TIMEOUT(set) &&
	    ip_set_timeout_expired(ext_timeout(data, set)))
		return false;
	if (SET_WITH_COUNTER(set)) {
		struct ip_set_counter *counter = ext_counter(data, set);

		if (flags & IPSET_FLAG_MATCH_COUNTERS &&
		    !(ip_set_match_counter(ip_set_get_packets(counter),
				mext->packets, mext->packets_op) &&
		      ip_set_match_counter(ip_set_get_bytes(counter),
				mext->bytes, mext->bytes_op)))
			return false;
		ip_set_update_counter(counter, ext, flags);
	}
	if (SET_WITH_SKBINFO(set))
		ip_set_get_skbinfo(ext_skbinfo(data, set),
				   ext, mext, flags);
	return true;
}