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
struct mp_decode {int /*<<< orphan*/  packets; } ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mp_decode_push_packet(struct mp_decode *decode, AVPacket *packet)
{
	circlebuf_push_back(&decode->packets, packet, sizeof(*packet));
}