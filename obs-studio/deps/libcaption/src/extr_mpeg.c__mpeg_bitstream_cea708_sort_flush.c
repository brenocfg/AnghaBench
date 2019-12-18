#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status; scalar_t__ latent; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;
struct TYPE_8__ {double timestamp; } ;

/* Variables and functions */
 scalar_t__ LIBCAPTION_OK ; 
 TYPE_5__* _mpeg_bitstream_cea708_front (TYPE_1__*) ; 
 int /*<<< orphan*/  _mpeg_bitstream_cea708_sort (TYPE_1__*) ; 
 int /*<<< orphan*/  mpeg_bitstream_flush (TYPE_1__*,int /*<<< orphan*/ *) ; 

void _mpeg_bitstream_cea708_sort_flush(mpeg_bitstream_t* packet, caption_frame_t* frame, double dts)
{
    _mpeg_bitstream_cea708_sort(packet);
    // Loop will terminate on LIBCAPTION_READY
    while (packet->latent && packet->status == LIBCAPTION_OK && _mpeg_bitstream_cea708_front(packet)->timestamp < dts) {
        mpeg_bitstream_flush(packet, frame);
    }
}