#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int end; } ;
struct sw_flow_match {TYPE_1__ range; struct sw_flow_key* key; } ;
struct sw_flow_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  unmasked_key; } ;
struct sw_flow {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int cmp_key (int /*<<< orphan*/ ,struct sw_flow_key*,int,int) ; 
 int flow_key_start (struct sw_flow_key*) ; 
 int /*<<< orphan*/  ovs_identifier_is_ufid (TYPE_2__*) ; 

__attribute__((used)) static bool ovs_flow_cmp_unmasked_key(const struct sw_flow *flow,
				      const struct sw_flow_match *match)
{
	struct sw_flow_key *key = match->key;
	int key_start = flow_key_start(key);
	int key_end = match->range.end;

	BUG_ON(ovs_identifier_is_ufid(&flow->id));
	return cmp_key(flow->id.unmasked_key, key, key_start, key_end);
}