#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t latent; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
struct TYPE_9__ {scalar_t__ timestamp; } ;
typedef  TYPE_2__ cea708_t ;

/* Variables and functions */
 TYPE_2__* _mpeg_bitstream_cea708_at (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

void _mpeg_bitstream_cea708_sort(mpeg_bitstream_t* packet)
{
    // TODO better sort? (for small nearly sorted lists bubble is difficult to beat)
    // This must be stable, decending sort
again:
    for (size_t i = 1; i < packet->latent; ++i) {
        cea708_t c;
        cea708_t* a = _mpeg_bitstream_cea708_at(packet, i - 1);
        cea708_t* b = _mpeg_bitstream_cea708_at(packet, i);
        if (a->timestamp > b->timestamp) {
            memcpy(&c, a, sizeof(cea708_t));
            memcpy(a, b, sizeof(cea708_t));
            memcpy(b, &c, sizeof(cea708_t));
            goto again;
        }
    }
}