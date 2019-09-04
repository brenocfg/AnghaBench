#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* val; scalar_t__ len; int /*<<< orphan*/  const* encoding; int /*<<< orphan*/  no_language; } ;
typedef  TYPE_1__ mbfl_string ;
typedef  int /*<<< orphan*/  mbfl_language_id ;
typedef  int /*<<< orphan*/  mbfl_encoding ;

/* Variables and functions */

void
mbfl_string_init_set(mbfl_string *string, mbfl_language_id no_language, const mbfl_encoding *encoding)
{
	if (string) {
		string->no_language = no_language;
		string->encoding = encoding;
		string->val = (unsigned char*)NULL;
		string->len = 0;
	}
}