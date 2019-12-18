#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbfl_encoding ;
struct TYPE_8__ {scalar_t__ filter_flush; scalar_t__ filter_function; } ;
struct TYPE_7__ {TYPE_2__ device; int /*<<< orphan*/ * filter1; TYPE_2__* filter2; int /*<<< orphan*/  const* from; int /*<<< orphan*/  const* to; } ;
typedef  TYPE_1__ mbfl_buffer_converter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_delete (TYPE_2__*) ; 
 int /*<<< orphan*/ * mbfl_convert_filter_get_vtbl (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 void* mbfl_convert_filter_new (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int (*) (int,void*),int (*) (void*),TYPE_2__*) ; 
 int /*<<< orphan*/  const mbfl_encoding_wchar ; 
 int /*<<< orphan*/  mbfl_free (TYPE_1__*) ; 
 scalar_t__ mbfl_malloc (int) ; 
 int /*<<< orphan*/  mbfl_memory_device_init (TYPE_2__*,size_t,size_t) ; 
 int mbfl_memory_device_output (int,void*) ; 

mbfl_buffer_converter *
mbfl_buffer_converter_new(
	const mbfl_encoding *from,
	const mbfl_encoding *to,
    size_t buf_initsz)
{
	mbfl_buffer_converter *convd;

	/* allocate */
	convd = (mbfl_buffer_converter*)mbfl_malloc(sizeof(mbfl_buffer_converter));
	if (convd == NULL) {
		return NULL;
	}

	/* initialize */
	convd->from = from;
	convd->to = to;

	/* create convert filter */
	convd->filter1 = NULL;
	convd->filter2 = NULL;
	if (mbfl_convert_filter_get_vtbl(convd->from, convd->to) != NULL) {
		convd->filter1 = mbfl_convert_filter_new(convd->from, convd->to, mbfl_memory_device_output, NULL, &convd->device);
	} else {
		convd->filter2 = mbfl_convert_filter_new(&mbfl_encoding_wchar, convd->to, mbfl_memory_device_output, NULL, &convd->device);
		if (convd->filter2 != NULL) {
			convd->filter1 = mbfl_convert_filter_new(convd->from,
					&mbfl_encoding_wchar,
					(int (*)(int, void*))convd->filter2->filter_function,
					(int (*)(void*))convd->filter2->filter_flush,
					convd->filter2);
			if (convd->filter1 == NULL) {
				mbfl_convert_filter_delete(convd->filter2);
			}
		}
	}
	if (convd->filter1 == NULL) {
		mbfl_free(convd);
		return NULL;
	}

	mbfl_memory_device_init(&convd->device, buf_initsz, buf_initsz/4);

	return convd;
}