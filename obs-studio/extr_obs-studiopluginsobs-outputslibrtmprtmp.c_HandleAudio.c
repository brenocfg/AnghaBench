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
typedef  int /*<<< orphan*/  RTMPPacket ;
typedef  int /*<<< orphan*/  RTMP ;

/* Variables and functions */

__attribute__((used)) static void
HandleAudio(RTMP *r, const RTMPPacket *packet)
{
	(void)r;
	(void)packet;
}