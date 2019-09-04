#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t len; unsigned char* val; TYPE_2__* encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_10__ {int flag; unsigned char* mblen_table; } ;
typedef  TYPE_2__ mbfl_encoding ;
struct TYPE_11__ {int /*<<< orphan*/  (* filter_function ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
typedef  TYPE_3__ mbfl_convert_filter ;

/* Variables and functions */
 int MBFL_ENCTYPE_SBCS ; 
 int MBFL_ENCTYPE_WCS2BE ; 
 int MBFL_ENCTYPE_WCS2LE ; 
 int MBFL_ENCTYPE_WCS4BE ; 
 int MBFL_ENCTYPE_WCS4LE ; 
 int /*<<< orphan*/  filter_count_output ; 
 int /*<<< orphan*/  mbfl_convert_filter_delete (TYPE_3__*) ; 
 TYPE_3__* mbfl_convert_filter_new (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mbfl_encoding_wchar ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

size_t
mbfl_strlen(mbfl_string *string)
{
	size_t len, n, k;
	unsigned char *p;
	const mbfl_encoding *encoding = string->encoding;

	len = 0;
	if (encoding->flag & MBFL_ENCTYPE_SBCS) {
		len = string->len;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS2BE | MBFL_ENCTYPE_WCS2LE)) {
		len = string->len/2;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS4BE | MBFL_ENCTYPE_WCS4LE)) {
		len = string->len/4;
	} else if (encoding->mblen_table != NULL) {
		const unsigned char *mbtab = encoding->mblen_table;
		n = 0;
		p = string->val;
		k = string->len;
		/* count */
		if (p != NULL) {
			while (n < k) {
				unsigned m = mbtab[*p];
				n += m;
				p += m;
				len++;
			}
		}
	} else {
		/* wchar filter */
		mbfl_convert_filter *filter = mbfl_convert_filter_new(
		  string->encoding,
		  &mbfl_encoding_wchar,
		  filter_count_output, 0, &len);
		if (filter == NULL) {
			return (size_t) -1;
		}
		/* count */
		n = string->len;
		p = string->val;
		if (p != NULL) {
			while (n > 0) {
				(*filter->filter_function)(*p++, filter);
				n--;
			}
		}
		mbfl_convert_filter_delete(filter);
	}

	return len;
}