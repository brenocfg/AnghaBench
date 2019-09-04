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
struct qlink_mac_address {int dummy; } ;
struct qlink_acl_data {int dummy; } ;
struct cfg80211_acl_data {int n_acl_entries; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t qtnf_cmd_acl_data_size(const struct cfg80211_acl_data *acl)
{
	size_t size = sizeof(struct qlink_acl_data) +
		      acl->n_acl_entries * sizeof(struct qlink_mac_address);

	return size;
}