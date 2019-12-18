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
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {int len; char const* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int strlen (char const*) ; 

__attribute__((used)) static text *
catenate_stringinfo_string(StringInfo buffer, const char *addon)
{
	/* custom version of cstring_to_text_with_len */
	int			buflen = buffer->len;
	int			addlen = strlen(addon);
	text	   *result = (text *) palloc(buflen + addlen + VARHDRSZ);

	SET_VARSIZE(result, buflen + addlen + VARHDRSZ);
	memcpy(VARDATA(result), buffer->data, buflen);
	memcpy(VARDATA(result) + buflen, addon, addlen);

	return result;
}