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
struct dsa_switch {scalar_t__ index; } ;
struct dsa_notifier_mdb_info {scalar_t__ sw_index; int port; } ;

/* Variables and functions */
 scalar_t__ dsa_is_dsa_port (struct dsa_switch*,int) ; 

__attribute__((used)) static bool dsa_switch_mdb_match(struct dsa_switch *ds, int port,
				 struct dsa_notifier_mdb_info *info)
{
	if (ds->index == info->sw_index && port == info->port)
		return true;

	if (dsa_is_dsa_port(ds, port))
		return true;

	return false;
}