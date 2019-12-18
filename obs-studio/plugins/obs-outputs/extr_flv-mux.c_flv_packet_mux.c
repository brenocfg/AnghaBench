#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct serializer {int dummy; } ;
struct encoder_packet {scalar_t__ type; } ;
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct array_output_data {TYPE_1__ bytes; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  array_output_serializer_init (struct serializer*,struct array_output_data*) ; 
 int /*<<< orphan*/  flv_audio (struct serializer*,int /*<<< orphan*/ ,struct encoder_packet*,int) ; 
 int /*<<< orphan*/  flv_video (struct serializer*,int /*<<< orphan*/ ,struct encoder_packet*,int) ; 

void flv_packet_mux(struct encoder_packet *packet, int32_t dts_offset,
		    uint8_t **output, size_t *size, bool is_header)
{
	struct array_output_data data;
	struct serializer s;

	array_output_serializer_init(&s, &data);

	if (packet->type == OBS_ENCODER_VIDEO)
		flv_video(&s, dts_offset, packet, is_header);
	else
		flv_audio(&s, dts_offset, packet, is_header);

	*output = data.bytes.array;
	*size = data.bytes.num;
}