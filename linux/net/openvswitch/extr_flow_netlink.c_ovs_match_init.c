#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sw_flow_match {struct sw_flow_mask* mask; struct sw_flow_match* key; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;
struct sw_flow_mask {TYPE_1__ range; struct sw_flow_match key; } ;
struct sw_flow_key {struct sw_flow_mask* mask; struct sw_flow_key* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct sw_flow_match*,int /*<<< orphan*/ ,int) ; 

void ovs_match_init(struct sw_flow_match *match,
		    struct sw_flow_key *key,
		    bool reset_key,
		    struct sw_flow_mask *mask)
{
	memset(match, 0, sizeof(*match));
	match->key = key;
	match->mask = mask;

	if (reset_key)
		memset(key, 0, sizeof(*key));

	if (mask) {
		memset(&mask->key, 0, sizeof(mask->key));
		mask->range.start = mask->range.end = 0;
	}
}