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
typedef  int /*<<< orphan*/  x264_picture_t ;
typedef  int /*<<< orphan*/  x264_nal_t ;
struct obs_x264 {int /*<<< orphan*/  context; } ;
struct encoder_packet {int dummy; } ;
struct encoder_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_pic_data (struct obs_x264*,int /*<<< orphan*/ *,struct encoder_frame*) ; 
 int /*<<< orphan*/  parse_packet (struct obs_x264*,struct encoder_packet*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int x264_encoder_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool obs_x264_encode(void *data, struct encoder_frame *frame,
			    struct encoder_packet *packet,
			    bool *received_packet)
{
	struct obs_x264 *obsx264 = data;
	x264_nal_t *nals;
	int nal_count;
	int ret;
	x264_picture_t pic, pic_out;

	if (!frame || !packet || !received_packet)
		return false;

	if (frame)
		init_pic_data(obsx264, &pic, frame);

	ret = x264_encoder_encode(obsx264->context, &nals, &nal_count,
				  (frame ? &pic : NULL), &pic_out);
	if (ret < 0) {
		warn("encode failed");
		return false;
	}

	*received_packet = (nal_count != 0);
	parse_packet(obsx264, packet, nals, nal_count, &pic_out);

	return true;
}