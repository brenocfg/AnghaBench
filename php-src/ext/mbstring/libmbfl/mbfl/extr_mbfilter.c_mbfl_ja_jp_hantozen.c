#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {size_t len; unsigned char* val; int /*<<< orphan*/ * encoding; int /*<<< orphan*/  no_language; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_22__ {scalar_t__ (* filter_function ) (int /*<<< orphan*/ ,TYPE_2__*) ;TYPE_3__* opaque; scalar_t__ filter_flush; } ;
typedef  TYPE_2__ mbfl_memory_device ;
struct TYPE_23__ {int mode; } ;
typedef  TYPE_3__ mbfl_filt_tl_jisx0201_jisx0208_param ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_convert_filter_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_convert_filter_flush (TYPE_2__*) ; 
 TYPE_2__* mbfl_convert_filter_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (int,void*),int (*) (void*),TYPE_2__*) ; 
 TYPE_2__* mbfl_convert_filter_new2 (int /*<<< orphan*/ *,int (*) (int,void*),int (*) (void*),TYPE_2__*) ; 
 int /*<<< orphan*/  mbfl_encoding_wchar ; 
 int /*<<< orphan*/  mbfl_free (TYPE_3__*) ; 
 scalar_t__ mbfl_malloc (int) ; 
 int /*<<< orphan*/  mbfl_memory_device_init (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int mbfl_memory_device_output (int,void*) ; 
 TYPE_1__* mbfl_memory_device_result (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbfl_string_init (TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vtbl_tl_jisx0201_jisx0208 ; 

mbfl_string *
mbfl_ja_jp_hantozen(
    mbfl_string *string,
    mbfl_string *result,
    int mode)
{
	size_t n;
	unsigned char *p;
	mbfl_memory_device device;
	mbfl_convert_filter *decoder = NULL;
	mbfl_convert_filter *encoder = NULL;
	mbfl_convert_filter *tl_filter = NULL;
	mbfl_convert_filter *next_filter = NULL;
	mbfl_filt_tl_jisx0201_jisx0208_param *param = NULL;

	mbfl_memory_device_init(&device, string->len, 0);
	mbfl_string_init(result);

	result->no_language = string->no_language;
	result->encoding = string->encoding;

	decoder = mbfl_convert_filter_new(
		&mbfl_encoding_wchar,
		string->encoding,
		mbfl_memory_device_output, 0, &device);
	if (decoder == NULL) {
		goto out;
	}
	next_filter = decoder;

	param =
		(mbfl_filt_tl_jisx0201_jisx0208_param *)mbfl_malloc(sizeof(mbfl_filt_tl_jisx0201_jisx0208_param));
	if (param == NULL) {
		goto out;
	}

	param->mode = mode;

	tl_filter = mbfl_convert_filter_new2(
		&vtbl_tl_jisx0201_jisx0208,
		(int(*)(int, void*))next_filter->filter_function,
		(int(*)(void*))next_filter->filter_flush,
		next_filter);
	if (tl_filter == NULL) {
		mbfl_free(param);
		goto out;
	}

	tl_filter->opaque = param;
	next_filter = tl_filter;

	encoder = mbfl_convert_filter_new(
		string->encoding,
		&mbfl_encoding_wchar,
		(int(*)(int, void*))next_filter->filter_function,
		(int(*)(void*))next_filter->filter_flush,
		next_filter);
	if (encoder == NULL) {
		goto out;
	}

	/* feed data */
	p = string->val;
	n = string->len;
	if (p != NULL) {
		while (n > 0) {
			if ((*encoder->filter_function)(*p++, encoder) < 0) {
				break;
			}
			n--;
		}
	}

	mbfl_convert_filter_flush(encoder);
	result = mbfl_memory_device_result(&device, result);
out:
	if (tl_filter != NULL) {
		if (tl_filter->opaque != NULL) {
			mbfl_free(tl_filter->opaque);
		}
		mbfl_convert_filter_delete(tl_filter);
	}

	if (decoder != NULL) {
		mbfl_convert_filter_delete(decoder);
	}

	if (encoder != NULL) {
		mbfl_convert_filter_delete(encoder);
	}

	return result;
}