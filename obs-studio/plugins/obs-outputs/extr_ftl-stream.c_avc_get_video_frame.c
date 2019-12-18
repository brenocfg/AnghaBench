#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {size_t total; TYPE_2__* nalus; } ;
struct ftl_stream {TYPE_1__ coded_pic_buffer; } ;
struct encoder_packet {size_t size; unsigned char* data; } ;
struct TYPE_4__ {unsigned char* data; int len; int send_marker_bit; } ;
typedef  TYPE_2__ nalu_t ;

/* Variables and functions */
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int avc_get_video_frame(struct ftl_stream *stream,
			       struct encoder_packet *packet, bool is_header)
{
	int consumed = 0;
	int len = (int)packet->size;
	nalu_t *nalu;

	unsigned char *video_stream = packet->data;

	while ((size_t)consumed < packet->size) {
		size_t total_max = sizeof(stream->coded_pic_buffer.nalus) /
				   sizeof(stream->coded_pic_buffer.nalus[0]);

		if ((size_t)stream->coded_pic_buffer.total >= total_max) {
			warn("ERROR: cannot continue, nalu buffers are full");
			return -1;
		}

		nalu = &stream->coded_pic_buffer
				.nalus[stream->coded_pic_buffer.total];

		if (is_header) {
			if (consumed == 0) {
				//first 6 bytes are some obs header with part
				//of the sps
				video_stream += 6;
				consumed += 6;
			} else {
				//another spacer byte of 0x1
				video_stream += 1;
				consumed += 1;
			}

			len = video_stream[0] << 8 | video_stream[1];
			video_stream += 2;
			consumed += 2;
		} else {
			len = video_stream[0] << 24 | video_stream[1] << 16 |
			      video_stream[2] << 8 | video_stream[3];

			if ((size_t)len > (packet->size - (size_t)consumed)) {
				warn("ERROR: got len of %d but packet only "
				     "has %d left",
				     len, (int)(packet->size - consumed));
			}

			consumed += 4;
			video_stream += 4;
		}

		consumed += len;

		uint8_t nalu_type = video_stream[0] & 0x1F;
		uint8_t nri = (video_stream[0] >> 5) & 0x3;

		if ((nalu_type != 12 && nalu_type != 6 && nalu_type != 9) ||
		    nri) {
			nalu->data = video_stream;
			nalu->len = len;
			nalu->send_marker_bit = 0;
			stream->coded_pic_buffer.total++;
		}

		video_stream += len;
	}

	if (!is_header) {
		size_t idx = stream->coded_pic_buffer.total - 1;
		stream->coded_pic_buffer.nalus[idx].send_marker_bit = 1;
	}

	return 0;
}