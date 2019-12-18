#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (void*) ; 
 char* quote_identifier (char const*) ; 

__attribute__((used)) static char *
quote_object_name(const char *src1, const char *src2,
				  const char *src3, const char *src4)
{
	StringInfoData result;
	const char *temp;

	initStringInfo(&result);

	if (src1)
	{
		temp = quote_identifier(src1);
		appendStringInfoString(&result, temp);
		if (src1 != temp)
			pfree((void *) temp);
	}
	if (src2)
	{
		temp = quote_identifier(src2);
		appendStringInfo(&result, ".%s", temp);
		if (src2 != temp)
			pfree((void *) temp);
	}
	if (src3)
	{
		temp = quote_identifier(src3);
		appendStringInfo(&result, ".%s", temp);
		if (src3 != temp)
			pfree((void *) temp);
	}
	if (src4)
	{
		temp = quote_identifier(src4);
		appendStringInfo(&result, ".%s", temp);
		if (src4 != temp)
			pfree((void *) temp);
	}
	return result.data;
}