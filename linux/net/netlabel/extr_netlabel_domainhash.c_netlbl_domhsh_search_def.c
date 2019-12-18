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
typedef  scalar_t__ u16 ;
struct netlbl_dom_map {scalar_t__ valid; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  netlbl_domhsh_def_ipv4 ; 
 int /*<<< orphan*/  netlbl_domhsh_def_ipv6 ; 
 struct netlbl_dom_map* netlbl_domhsh_rcu_deref (int /*<<< orphan*/ ) ; 
 struct netlbl_dom_map* netlbl_domhsh_search (char const*,scalar_t__) ; 

__attribute__((used)) static struct netlbl_dom_map *netlbl_domhsh_search_def(const char *domain,
						       u16 family)
{
	struct netlbl_dom_map *entry;

	entry = netlbl_domhsh_search(domain, family);
	if (entry != NULL)
		return entry;
	if (family == AF_INET || family == AF_UNSPEC) {
		entry = netlbl_domhsh_rcu_deref(netlbl_domhsh_def_ipv4);
		if (entry != NULL && entry->valid)
			return entry;
	}
	if (family == AF_INET6 || family == AF_UNSPEC) {
		entry = netlbl_domhsh_rcu_deref(netlbl_domhsh_def_ipv6);
		if (entry != NULL && entry->valid)
			return entry;
	}

	return NULL;
}