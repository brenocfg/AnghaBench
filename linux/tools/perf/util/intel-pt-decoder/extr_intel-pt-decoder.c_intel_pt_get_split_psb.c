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
struct intel_pt_decoder {int pos; scalar_t__ len; scalar_t__ temp_buf; scalar_t__ buf; scalar_t__ next_len; scalar_t__ next_buf; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_PSB_LEN ; 
 int /*<<< orphan*/  INTEL_PT_PSB_STR ; 
 int intel_pt_get_next_data (struct intel_pt_decoder*,int) ; 
 int intel_pt_rest_psb (struct intel_pt_decoder*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int intel_pt_get_split_psb(struct intel_pt_decoder *decoder,
				  int part_psb)
{
	int rest_psb, ret;

	decoder->pos += decoder->len;
	decoder->len = 0;

	ret = intel_pt_get_next_data(decoder, false);
	if (ret)
		return ret;

	rest_psb = intel_pt_rest_psb(decoder, part_psb);
	if (!rest_psb)
		return 0;

	decoder->pos -= part_psb;
	decoder->next_buf = decoder->buf + rest_psb;
	decoder->next_len = decoder->len - rest_psb;
	memcpy(decoder->temp_buf, INTEL_PT_PSB_STR, INTEL_PT_PSB_LEN);
	decoder->buf = decoder->temp_buf;
	decoder->len = INTEL_PT_PSB_LEN;

	return 0;
}