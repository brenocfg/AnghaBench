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
struct sctp_packet {int /*<<< orphan*/ * auth; scalar_t__ ipfragok; scalar_t__ has_auth; scalar_t__ has_data; scalar_t__ has_sack; scalar_t__ has_cookie_echo; int /*<<< orphan*/  overhead; int /*<<< orphan*/  size; } ;

/* Variables and functions */

__attribute__((used)) static void sctp_packet_reset(struct sctp_packet *packet)
{
	/* sctp_packet_transmit() relies on this to reset size to the
	 * current overhead after sending packets.
	 */
	packet->size = packet->overhead;

	packet->has_cookie_echo = 0;
	packet->has_sack = 0;
	packet->has_data = 0;
	packet->has_auth = 0;
	packet->ipfragok = 0;
	packet->auth = NULL;
}