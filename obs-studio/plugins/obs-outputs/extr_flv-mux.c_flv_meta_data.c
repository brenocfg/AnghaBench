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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct serializer {int dummy; } ;
struct TYPE_2__ {char* array; size_t num; } ;
struct array_output_data {TYPE_1__ bytes; } ;
typedef  int /*<<< orphan*/  obs_output_t ;

/* Variables and functions */
 int RTMP_PACKET_TYPE_INFO ; 
 int /*<<< orphan*/  array_output_serializer_init (struct serializer*,struct array_output_data*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  build_flv_meta_data (int /*<<< orphan*/ *,char**,size_t*,size_t) ; 
 int /*<<< orphan*/  s_w8 (struct serializer*,int) ; 
 int /*<<< orphan*/  s_wb24 (struct serializer*,int) ; 
 int /*<<< orphan*/  s_wb32 (struct serializer*,int) ; 
 int /*<<< orphan*/  s_write (struct serializer*,char*,size_t) ; 
 int serializer_get_pos (struct serializer*) ; 

bool flv_meta_data(obs_output_t *context, uint8_t **output, size_t *size,
		   bool write_header, size_t audio_idx)
{
	struct array_output_data data;
	struct serializer s;
	uint8_t *meta_data = NULL;
	size_t meta_data_size;
	uint32_t start_pos;

	array_output_serializer_init(&s, &data);

	if (!build_flv_meta_data(context, &meta_data, &meta_data_size,
				 audio_idx)) {
		bfree(meta_data);
		return false;
	}

	if (write_header) {
		s_write(&s, "FLV", 3);
		s_w8(&s, 1);
		s_w8(&s, 5);
		s_wb32(&s, 9);
		s_wb32(&s, 0);
	}

	start_pos = serializer_get_pos(&s);

	s_w8(&s, RTMP_PACKET_TYPE_INFO);

	s_wb24(&s, (uint32_t)meta_data_size);
	s_wb32(&s, 0);
	s_wb24(&s, 0);

	s_write(&s, meta_data, meta_data_size);

	s_wb32(&s, (uint32_t)serializer_get_pos(&s) - start_pos - 1);

	*output = data.bytes.array;
	*size = data.bytes.num;

	bfree(meta_data);
	return true;
}