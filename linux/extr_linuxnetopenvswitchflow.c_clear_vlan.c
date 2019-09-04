#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tpid; scalar_t__ tci; } ;
struct TYPE_4__ {scalar_t__ tpid; scalar_t__ tci; } ;
struct TYPE_6__ {TYPE_2__ cvlan; TYPE_1__ vlan; } ;
struct sw_flow_key {TYPE_3__ eth; } ;

/* Variables and functions */

__attribute__((used)) static void clear_vlan(struct sw_flow_key *key)
{
	key->eth.vlan.tci = 0;
	key->eth.vlan.tpid = 0;
	key->eth.cvlan.tci = 0;
	key->eth.cvlan.tpid = 0;
}