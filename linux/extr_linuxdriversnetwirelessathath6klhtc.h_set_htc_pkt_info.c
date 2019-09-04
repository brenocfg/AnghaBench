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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct htc_packet {unsigned int act_len; int endpoint; TYPE_2__ info; int /*<<< orphan*/ * buf; void* pkt_cntxt; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */

__attribute__((used)) static inline void set_htc_pkt_info(struct htc_packet *packet, void *context,
				    u8 *buf, unsigned int len,
				    enum htc_endpoint_id eid, u16 tag)
{
	packet->pkt_cntxt = context;
	packet->buf = buf;
	packet->act_len = len;
	packet->endpoint = eid;
	packet->info.tx.tag = tag;
}