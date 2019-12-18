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
struct TYPE_2__ {int type; int count; scalar_t__ payload; } ;
struct test_data {int len; int new_ctx; TYPE_1__ packet; } ;
struct intel_pt_pkt {int type; int count; scalar_t__ payload; } ;
typedef  enum intel_pt_pkt_ctx { ____Placeholder_intel_pt_pkt_ctx } intel_pt_pkt_ctx ;

/* Variables and functions */
 int TEST_FAIL ; 
 int /*<<< orphan*/  decoding_failed (struct test_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int) ; 

__attribute__((used)) static int fail(struct test_data *d, struct intel_pt_pkt *packet, int len,
		enum intel_pt_pkt_ctx new_ctx)
{
	decoding_failed(d);

	if (len != d->len)
		pr_debug("Expected length: %d   Decoded length %d\n",
			 d->len, len);

	if (packet->type != d->packet.type)
		pr_debug("Expected type: %d   Decoded type %d\n",
			 d->packet.type, packet->type);

	if (packet->count != d->packet.count)
		pr_debug("Expected count: %d   Decoded count %d\n",
			 d->packet.count, packet->count);

	if (packet->payload != d->packet.payload)
		pr_debug("Expected payload: 0x%llx   Decoded payload 0x%llx\n",
			 (unsigned long long)d->packet.payload,
			 (unsigned long long)packet->payload);

	if (new_ctx != d->new_ctx)
		pr_debug("Expected packet context: %d   Decoded packet context %d\n",
			 d->new_ctx, new_ctx);

	return TEST_FAIL;
}