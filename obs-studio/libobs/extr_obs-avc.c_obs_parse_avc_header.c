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
typedef  int /*<<< orphan*/  uint16_t ;
struct serializer {int dummy; } ;
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct array_output_data {TYPE_1__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_output_serializer_init (struct serializer*,struct array_output_data*) ; 
 int /*<<< orphan*/ * bmemdup (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  get_sps_pps (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  has_start_code (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  s_w8 (struct serializer*,int) ; 
 int /*<<< orphan*/  s_wb16 (struct serializer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_write (struct serializer*,int /*<<< orphan*/  const*,size_t) ; 

size_t obs_parse_avc_header(uint8_t **header, const uint8_t *data, size_t size)
{
	struct array_output_data output;
	struct serializer s;
	const uint8_t *sps = NULL, *pps = NULL;
	size_t sps_size = 0, pps_size = 0;

	array_output_serializer_init(&s, &output);

	if (size <= 6)
		return 0;

	if (!has_start_code(data)) {
		*header = bmemdup(data, size);
		return size;
	}

	get_sps_pps(data, size, &sps, &sps_size, &pps, &pps_size);
	if (!sps || !pps || sps_size < 4)
		return 0;

	s_w8(&s, 0x01);
	s_write(&s, sps + 1, 3);
	s_w8(&s, 0xff);
	s_w8(&s, 0xe1);

	s_wb16(&s, (uint16_t)sps_size);
	s_write(&s, sps, sps_size);
	s_w8(&s, 0x01);
	s_wb16(&s, (uint16_t)pps_size);
	s_write(&s, pps, pps_size);

	*header = output.bytes.array;
	return output.bytes.num;
}