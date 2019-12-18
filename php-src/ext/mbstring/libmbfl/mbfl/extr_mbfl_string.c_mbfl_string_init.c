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
struct TYPE_3__ {unsigned char* val; scalar_t__ len; int /*<<< orphan*/ * encoding; int /*<<< orphan*/  no_language; } ;
typedef  TYPE_1__ mbfl_string ;

/* Variables and functions */
 int /*<<< orphan*/  mbfl_encoding_pass ; 
 int /*<<< orphan*/  mbfl_no_language_uni ; 

void
mbfl_string_init(mbfl_string *string)
{
	if (string) {
		string->no_language = mbfl_no_language_uni;
		string->encoding = &mbfl_encoding_pass;
		string->val = (unsigned char*)NULL;
		string->len = 0;
	}
}