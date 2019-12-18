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
struct tcf_proto {scalar_t__ prio; scalar_t__ protocol; TYPE_1__* chain; } ;
struct TYPE_2__ {scalar_t__ index; } ;

/* Variables and functions */

__attribute__((used)) static bool tcf_proto_cmp(const struct tcf_proto *tp1,
			  const struct tcf_proto *tp2)
{
	return tp1->chain->index == tp2->chain->index &&
	       tp1->prio == tp2->prio &&
	       tp1->protocol == tp2->protocol;
}