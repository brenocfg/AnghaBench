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
struct htc_packet {scalar_t__ act_len; int /*<<< orphan*/  buf_start; int /*<<< orphan*/  buf; } ;

/* Variables and functions */

__attribute__((used)) static inline void htc_rxpkt_reset(struct htc_packet *packet)
{
	packet->buf = packet->buf_start;
	packet->act_len = 0;
}