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
struct sw_flow_key {int mac_proto; } ;

/* Variables and functions */
 int SW_FLOW_KEY_INVALID ; 

__attribute__((used)) static bool is_flow_key_valid(const struct sw_flow_key *key)
{
	return !(key->mac_proto & SW_FLOW_KEY_INVALID);
}