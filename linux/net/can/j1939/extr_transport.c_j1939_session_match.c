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
struct j1939_addr {scalar_t__ type; scalar_t__ src_name; scalar_t__ dst_name; scalar_t__ sa; scalar_t__ da; } ;

/* Variables and functions */

__attribute__((used)) static bool j1939_session_match(struct j1939_addr *se_addr,
				struct j1939_addr *sk_addr, bool reverse)
{
	if (se_addr->type != sk_addr->type)
		return false;

	if (reverse) {
		if (se_addr->src_name) {
			if (se_addr->src_name != sk_addr->dst_name)
				return false;
		} else if (se_addr->sa != sk_addr->da) {
			return false;
		}

		if (se_addr->dst_name) {
			if (se_addr->dst_name != sk_addr->src_name)
				return false;
		} else if (se_addr->da != sk_addr->sa) {
			return false;
		}
	} else {
		if (se_addr->src_name) {
			if (se_addr->src_name != sk_addr->src_name)
				return false;
		} else if (se_addr->sa != sk_addr->sa) {
			return false;
		}

		if (se_addr->dst_name) {
			if (se_addr->dst_name != sk_addr->dst_name)
				return false;
		} else if (se_addr->da != sk_addr->da) {
			return false;
		}
	}

	return true;
}