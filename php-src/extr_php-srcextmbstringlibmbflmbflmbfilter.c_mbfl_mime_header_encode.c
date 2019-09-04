#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mime_header_encoder_data {int* lwsp; size_t lwsplen; int firstindent; TYPE_2__* conv1_filter; } ;
struct TYPE_9__ {size_t len; unsigned char* val; int /*<<< orphan*/ * encoding; int /*<<< orphan*/  no_language; } ;
typedef  TYPE_1__ mbfl_string ;
typedef  int /*<<< orphan*/  mbfl_encoding ;
struct TYPE_10__ {int /*<<< orphan*/  (* filter_function ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_encoding_ascii ; 
 int /*<<< orphan*/  mbfl_string_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mime_header_encoder_delete (struct mime_header_encoder_data*) ; 
 struct mime_header_encoder_data* mime_header_encoder_new (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* mime_header_encoder_result (struct mime_header_encoder_data*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

mbfl_string *
mbfl_mime_header_encode(
    mbfl_string *string,
    mbfl_string *result,
    const mbfl_encoding *outcode,
    const mbfl_encoding *encoding,
    const char *linefeed,
    int indent)
{
	size_t n;
	unsigned char *p;
	struct mime_header_encoder_data *pe;

	mbfl_string_init(result);
	result->no_language = string->no_language;
	result->encoding = &mbfl_encoding_ascii;

	pe = mime_header_encoder_new(string->encoding, outcode, encoding);
	if (pe == NULL) {
		return NULL;
	}

	if (linefeed != NULL) {
		n = 0;
		while (*linefeed && n < 8) {
			pe->lwsp[n++] = *linefeed++;
		}
		pe->lwsp[n++] = 0x20;
		pe->lwsp[n] = '\0';
		pe->lwsplen = n;
	}
	if (indent > 0 && indent < 74) {
		pe->firstindent = indent;
	}

	n = string->len;
	p = string->val;
	while (n > 0) {
		(*pe->conv1_filter->filter_function)(*p++, pe->conv1_filter);
		n--;
	}

	result = mime_header_encoder_result(pe, result);
	mime_header_encoder_delete(pe);

	return result;
}