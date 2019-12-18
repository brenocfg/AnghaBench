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
struct mime_header_decoder_data {int /*<<< orphan*/ * deco_filter; int /*<<< orphan*/ * conv2_filter; int /*<<< orphan*/ * conv1_filter; int /*<<< orphan*/  const* encoding; int /*<<< orphan*/  const* incode; int /*<<< orphan*/  outdev; int /*<<< orphan*/  const* outcode; scalar_t__ status; scalar_t__ cspos; int /*<<< orphan*/  tmpdev; } ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */
 void* mbfl_convert_filter_new (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const mbfl_encoding_8bit ; 
 int /*<<< orphan*/  const mbfl_encoding_ascii ; 
 int /*<<< orphan*/  const mbfl_encoding_wchar ; 
 int /*<<< orphan*/  mbfl_filter_output_pipe ; 
 scalar_t__ mbfl_malloc (int) ; 
 int /*<<< orphan*/  mbfl_memory_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbfl_memory_device_output ; 
 int /*<<< orphan*/  mime_header_decoder_delete (struct mime_header_decoder_data*) ; 

struct mime_header_decoder_data*
mime_header_decoder_new(const mbfl_encoding *outcode)
{
	struct mime_header_decoder_data *pd;

	pd = (struct mime_header_decoder_data*)mbfl_malloc(sizeof(struct mime_header_decoder_data));
	if (pd == NULL) {
		return NULL;
	}

	mbfl_memory_device_init(&pd->outdev, 0, 0);
	mbfl_memory_device_init(&pd->tmpdev, 0, 0);
	pd->cspos = 0;
	pd->status = 0;
	pd->encoding = &mbfl_encoding_8bit;
	pd->incode = &mbfl_encoding_ascii;
	pd->outcode = outcode;
	/* charset convert filter */
	pd->conv2_filter = mbfl_convert_filter_new(&mbfl_encoding_wchar, pd->outcode, mbfl_memory_device_output, 0, &pd->outdev);
	pd->conv1_filter = mbfl_convert_filter_new(pd->incode, &mbfl_encoding_wchar, mbfl_filter_output_pipe, 0, pd->conv2_filter);
	/* decode filter */
	pd->deco_filter = mbfl_convert_filter_new(pd->encoding, &mbfl_encoding_8bit, mbfl_filter_output_pipe, 0, pd->conv1_filter);

	if (pd->conv1_filter == NULL || pd->conv2_filter == NULL || pd->deco_filter == NULL) {
		mime_header_decoder_delete(pd);
		return NULL;
	}

	return pd;
}