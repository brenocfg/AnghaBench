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
typedef  int /*<<< orphan*/  u8 ;
struct mac80211_hwsim_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_radios_rht ; 
 int /*<<< orphan*/  hwsim_rht_params ; 
 struct mac80211_hwsim_data* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mac80211_hwsim_data *get_hwsim_data_ref_from_addr(const u8 *addr)
{
	return rhashtable_lookup_fast(&hwsim_radios_rht,
				      addr,
				      hwsim_rht_params);
}