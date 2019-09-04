#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int len; unsigned char* val; int /*<<< orphan*/  const* encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_17__ {scalar_t__ (* filter_function ) (int /*<<< orphan*/ ,TYPE_2__*) ;int illegal_substchar; int /*<<< orphan*/  illegal_mode; } ;
typedef  TYPE_2__ mbfl_memory_device ;
typedef  int /*<<< orphan*/  mbfl_encoding ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR ; 
 int /*<<< orphan*/  mbfl_convert_filter_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_convert_filter_flush (TYPE_2__*) ; 
 int /*<<< orphan*/ * mbfl_convert_filter_get_vtbl (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_2__* mbfl_convert_filter_new (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int (*) (int,void*),int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  const mbfl_encoding_wchar ; 
 int /*<<< orphan*/  mbfl_memory_device_init (TYPE_2__*,int,int) ; 
 int mbfl_memory_device_output (int,void*) ; 
 TYPE_1__* mbfl_memory_device_result (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

mbfl_string *
mbfl_convert_encoding(
    mbfl_string *string,
    mbfl_string *result,
    const mbfl_encoding *toenc)
{
	size_t n;
	unsigned char *p;
	mbfl_memory_device device;
	mbfl_convert_filter *filter1;
	mbfl_convert_filter *filter2;

	/* initialize */
	if (toenc == NULL || string == NULL || result == NULL) {
		return NULL;
	}

	filter1 = NULL;
	filter2 = NULL;
	if (mbfl_convert_filter_get_vtbl(string->encoding, toenc) != NULL) {
		filter1 = mbfl_convert_filter_new(string->encoding, toenc, mbfl_memory_device_output, 0, &device);
	} else {
		filter2 = mbfl_convert_filter_new(&mbfl_encoding_wchar, toenc, mbfl_memory_device_output, 0, &device);
		if (filter2 != NULL) {
			filter1 = mbfl_convert_filter_new(string->encoding, &mbfl_encoding_wchar, (int (*)(int, void*))filter2->filter_function, NULL, filter2);
			if (filter1 == NULL) {
				mbfl_convert_filter_delete(filter2);
			}
		}
	}
	if (filter1 == NULL) {
		return NULL;
	}

	if (filter2 != NULL) {
		filter2->illegal_mode = MBFL_OUTPUTFILTER_ILLEGAL_MODE_CHAR;
		filter2->illegal_substchar = 0x3f;		/* '?' */
	}

	mbfl_memory_device_init(&device, string->len, (string->len >> 2) + 8);

	/* feed data */
	n = string->len;
	p = string->val;
	if (p != NULL) {
		while (n > 0) {
			if ((*filter1->filter_function)(*p++, filter1) < 0) {
				break;
			}
			n--;
		}
	}

	mbfl_convert_filter_flush(filter1);
	mbfl_convert_filter_delete(filter1);
	if (filter2 != NULL) {
		mbfl_convert_filter_flush(filter2);
		mbfl_convert_filter_delete(filter2);
	}

	return mbfl_memory_device_result(&device, result);
}