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
struct TYPE_2__ {int /*<<< orphan*/  labels; scalar_t__ mark; } ;
struct sw_flow_key {scalar_t__ ct_orig_proto; TYPE_1__ ct; scalar_t__ ct_zone; scalar_t__ ct_state; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ovs_ct_fill_key(const struct sk_buff *skb,
				   struct sw_flow_key *key)
{
	key->ct_state = 0;
	key->ct_zone = 0;
	key->ct.mark = 0;
	memset(&key->ct.labels, 0, sizeof(key->ct.labels));
	/* Clear 'ct_orig_proto' to mark the non-existence of original
	 * direction key fields.
	 */
	key->ct_orig_proto = 0;
}