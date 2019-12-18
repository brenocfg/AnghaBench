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
struct bpf_sock {int /*<<< orphan*/  state; int /*<<< orphan*/  dst_port; int /*<<< orphan*/ * dst_ip6; int /*<<< orphan*/  dst_ip4; int /*<<< orphan*/  src_port; int /*<<< orphan*/ * src_ip6; int /*<<< orphan*/  src_ip4; int /*<<< orphan*/  priority; int /*<<< orphan*/  mark; int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  family; int /*<<< orphan*/  bound_dev_if; } ;

/* Variables and functions */

__attribute__((used)) static void skcpy(struct bpf_sock *dst,
		  const struct bpf_sock *src)
{
	dst->bound_dev_if = src->bound_dev_if;
	dst->family = src->family;
	dst->type = src->type;
	dst->protocol = src->protocol;
	dst->mark = src->mark;
	dst->priority = src->priority;
	dst->src_ip4 = src->src_ip4;
	dst->src_ip6[0] = src->src_ip6[0];
	dst->src_ip6[1] = src->src_ip6[1];
	dst->src_ip6[2] = src->src_ip6[2];
	dst->src_ip6[3] = src->src_ip6[3];
	dst->src_port = src->src_port;
	dst->dst_ip4 = src->dst_ip4;
	dst->dst_ip6[0] = src->dst_ip6[0];
	dst->dst_ip6[1] = src->dst_ip6[1];
	dst->dst_ip6[2] = src->dst_ip6[2];
	dst->dst_ip6[3] = src->dst_ip6[3];
	dst->dst_port = src->dst_port;
	dst->state = src->state;
}