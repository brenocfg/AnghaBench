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
struct sw_flow_id {scalar_t__ ufid_len; int /*<<< orphan*/  ufid; } ;
struct TYPE_2__ {scalar_t__ ufid_len; int /*<<< orphan*/  ufid; } ;
struct sw_flow {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool ovs_flow_cmp_ufid(const struct sw_flow *flow,
			      const struct sw_flow_id *sfid)
{
	if (flow->id.ufid_len != sfid->ufid_len)
		return false;

	return !memcmp(flow->id.ufid, sfid->ufid, sfid->ufid_len);
}