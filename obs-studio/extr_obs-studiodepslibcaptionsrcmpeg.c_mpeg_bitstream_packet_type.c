#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int size; int* data; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;

/* Variables and functions */
#define  STREAM_TYPE_H262 130 
#define  STREAM_TYPE_H264 129 
#define  STREAM_TYPE_H265 128 

uint8_t mpeg_bitstream_packet_type(mpeg_bitstream_t* packet, unsigned stream_type)
{
    if (4 > packet->size) {
        return 0;
    }
    switch (stream_type) {
    case STREAM_TYPE_H262:
        return packet->data[3];
    case STREAM_TYPE_H264:
        return packet->data[3] & 0x1F;
    case STREAM_TYPE_H265:
        return (packet->data[3] >> 1) & 0x3F;
    default:
        return 0;
    }
}