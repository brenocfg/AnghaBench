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
struct demux_packet {int /*<<< orphan*/  metadata; int /*<<< orphan*/  avpacket; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_packet_tags_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void packet_destroy(void *ptr)
{
    struct demux_packet *dp = ptr;
    av_packet_unref(dp->avpacket);
    mp_packet_tags_unref(dp->metadata);
}