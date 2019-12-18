#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sei_t ;
typedef  int /*<<< orphan*/  sei_message_t ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ status; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ mpeg_bitstream_t ;
typedef  int /*<<< orphan*/  cea708_t ;
typedef  int /*<<< orphan*/  caption_frame_t ;

/* Variables and functions */
#define  H262_SEI_PACKET 130 
#define  H264_SEI_PACKET 129 
#define  H265_SEI_PACKET 128 
 scalar_t__ LIBCAPTION_ERROR ; 
 scalar_t__ LIBCAPTION_OK ; 
 scalar_t__ MAX_NALU_SIZE ; 
 unsigned int STREAM_TYPE_H262 ; 
 unsigned int STREAM_TYPE_H264 ; 
 unsigned int STREAM_TYPE_H265 ; 
 int /*<<< orphan*/ * _mpeg_bitstream_cea708_emplace_back (TYPE_1__*,double) ; 
 int /*<<< orphan*/  _mpeg_bitstream_cea708_sort_flush (TYPE_1__*,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cea708_parse_h262 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cea708_parse_h264 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t find_start_code (int /*<<< orphan*/ *,size_t) ; 
 void* libcaption_status_update (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int mpeg_bitstream_packet_type (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  sei_message_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sei_message_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sei_message_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sei_message_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sei_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,double) ; 
 int /*<<< orphan*/  sei_type_user_data_registered_itu_t_t35 ; 

size_t mpeg_bitstream_parse(mpeg_bitstream_t* packet, caption_frame_t* frame, const uint8_t* data, size_t size, unsigned stream_type, double dts, double cts)
{
    if (MAX_NALU_SIZE <= packet->size) {
        packet->status = LIBCAPTION_ERROR;
        // fprintf(stderr, "LIBCAPTION_ERROR\n");
        return 0;
    }

    // consume upto MAX_NALU_SIZE bytes
    if (MAX_NALU_SIZE <= packet->size + size) {
        size = MAX_NALU_SIZE - packet->size;
    }

    sei_t sei;
    size_t header_size, scpos;
    packet->status = LIBCAPTION_OK;
    memcpy(&packet->data[packet->size], data, size);
    packet->size += size;

    while (packet->status == LIBCAPTION_OK && 0 < (scpos = find_start_code(&packet->data[0], packet->size))) {
        switch (mpeg_bitstream_packet_type(packet, stream_type)) {
        default:
            break;
        case H262_SEI_PACKET:
            header_size = 4;
            if (STREAM_TYPE_H262 == stream_type && scpos > header_size) {
                cea708_t* cea708 = _mpeg_bitstream_cea708_emplace_back(packet, dts + cts);
                packet->status = libcaption_status_update(packet->status, cea708_parse_h262(&packet->data[header_size], scpos - header_size, cea708));
                _mpeg_bitstream_cea708_sort_flush(packet, frame, dts);
            }
            break;
        case H264_SEI_PACKET:
        case H265_SEI_PACKET:
            header_size = STREAM_TYPE_H264 == stream_type ? 4 : STREAM_TYPE_H265 == stream_type ? 5 : 0;
            if (header_size && scpos > header_size) {
                packet->status = libcaption_status_update(packet->status, sei_parse(&sei, &packet->data[header_size], scpos - header_size, dts + cts));
                for (sei_message_t* msg = sei_message_head(&sei); msg; msg = sei_message_next(msg)) {
                    if (sei_type_user_data_registered_itu_t_t35 == sei_message_type(msg)) {
                        cea708_t* cea708 = _mpeg_bitstream_cea708_emplace_back(packet, dts + cts);
                        packet->status = libcaption_status_update(packet->status, cea708_parse_h264(sei_message_data(msg), sei_message_size(msg), cea708));
                        _mpeg_bitstream_cea708_sort_flush(packet, frame, dts);
                    }
                }
            }
            break;
        }

        packet->size -= scpos;
        memmove(&packet->data[0], &packet->data[scpos], packet->size);
    }

    return size;
}