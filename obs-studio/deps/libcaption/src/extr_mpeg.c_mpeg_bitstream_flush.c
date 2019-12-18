#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t latent; int front; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int MAX_REFRENCE_FRAMES ; 
 int /*<<< orphan*/ * _mpeg_bitstream_cea708_front (TYPE_1__*) ; 
 int /*<<< orphan*/  cea708_to_caption_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libcaption_status_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t mpeg_bitstream_flush(mpeg_bitstream_t* packet, caption_frame_t* frame)
{
    if (packet->latent) {
        cea708_t* cea708 = _mpeg_bitstream_cea708_front(packet);
        packet->status = libcaption_status_update(LIBCAPTION_OK, cea708_to_caption_frame(frame, cea708));
        packet->front = (packet->front + 1) % MAX_REFRENCE_FRAMES;
        --packet->latent;
    }

    return packet->latent;
}