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
typedef  int /*<<< orphan*/  u16 ;
struct sw_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ovs_mac_header_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_key_mac_proto (struct sw_flow_key const*) ; 

__attribute__((used)) static inline u16 ovs_mac_header_len(const struct sw_flow_key *key)
{
	return __ovs_mac_header_len(ovs_key_mac_proto(key));
}