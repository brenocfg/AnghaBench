#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mime_header_decoder_data {int dummy; } ;
struct TYPE_8__ {size_t len; unsigned char* val; int /*<<< orphan*/  const* encoding; int /*<<< orphan*/  no_language; } ;
typedef  TYPE_1__ mbfl_string ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_string_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mime_header_decoder_collector (int /*<<< orphan*/ ,struct mime_header_decoder_data*) ; 
 int /*<<< orphan*/  mime_header_decoder_delete (struct mime_header_decoder_data*) ; 
 struct mime_header_decoder_data* mime_header_decoder_new (int /*<<< orphan*/  const*) ; 
 TYPE_1__* mime_header_decoder_result (struct mime_header_decoder_data*,TYPE_1__*) ; 

mbfl_string *
mbfl_mime_header_decode(
    mbfl_string *string,
    mbfl_string *result,
    const mbfl_encoding *outcode)
{
	size_t n;
	unsigned char *p;
	struct mime_header_decoder_data *pd;

	mbfl_string_init(result);
	result->no_language = string->no_language;
	result->encoding = outcode;

	pd = mime_header_decoder_new(outcode);
	if (pd == NULL) {
		return NULL;
	}

	/* feed data */
	n = string->len;
	p = string->val;
	while (n > 0) {
		mime_header_decoder_collector(*p++, pd);
		n--;
	}

	result = mime_header_decoder_result(pd, result);
	mime_header_decoder_delete(pd);

	return result;
}