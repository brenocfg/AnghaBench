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
struct serializer {int dummy; } ;
struct encoder_packet {int /*<<< orphan*/  priority; int /*<<< orphan*/  drop_priority; scalar_t__ size; scalar_t__ data; int /*<<< orphan*/  keyframe; } ;
struct TYPE_2__ {scalar_t__ num; scalar_t__ array; } ;
struct array_output_data {TYPE_1__ bytes; } ;
typedef  int /*<<< orphan*/  ref ;

/* Variables and functions */
 int /*<<< orphan*/  array_output_serializer_init (struct serializer*,struct array_output_data*) ; 
 int /*<<< orphan*/  get_drop_priority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize (struct serializer*,long*,int) ; 
 int /*<<< orphan*/  serialize_avc_data (struct serializer*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void obs_parse_avc_packet(struct encoder_packet *avc_packet,
			  const struct encoder_packet *src)
{
	struct array_output_data output;
	struct serializer s;
	long ref = 1;

	array_output_serializer_init(&s, &output);
	*avc_packet = *src;

	serialize(&s, &ref, sizeof(ref));
	serialize_avc_data(&s, src->data, src->size, &avc_packet->keyframe,
			   &avc_packet->priority);

	avc_packet->data = output.bytes.array + sizeof(ref);
	avc_packet->size = output.bytes.num - sizeof(ref);
	avc_packet->drop_priority = get_drop_priority(avc_packet->priority);
}