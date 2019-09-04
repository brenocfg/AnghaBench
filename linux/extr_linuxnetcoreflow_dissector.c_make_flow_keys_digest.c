#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct flow_keys_digest {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_8__ {TYPE_3__ v4addrs; } ;
struct TYPE_6__ {int /*<<< orphan*/  ports; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;
struct flow_keys {TYPE_4__ addrs; TYPE_2__ ports; TYPE_1__ basic; } ;
struct _flow_keys_digest_data {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  ports; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  memset (struct flow_keys_digest*,int /*<<< orphan*/ ,int) ; 

void make_flow_keys_digest(struct flow_keys_digest *digest,
			   const struct flow_keys *flow)
{
	struct _flow_keys_digest_data *data =
	    (struct _flow_keys_digest_data *)digest;

	BUILD_BUG_ON(sizeof(*data) > sizeof(*digest));

	memset(digest, 0, sizeof(*digest));

	data->n_proto = flow->basic.n_proto;
	data->ip_proto = flow->basic.ip_proto;
	data->ports = flow->ports.ports;
	data->src = flow->addrs.v4addrs.src;
	data->dst = flow->addrs.v4addrs.dst;
}