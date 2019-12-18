#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int header; } ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_1__* StringInfo ;
typedef  int /*<<< orphan*/  JsonPathItem ;
typedef  TYPE_3__ JsonPath ;

/* Variables and functions */
 int JSONPATH_LAX ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  jspInit (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  printJsonPathItem (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static char *
jsonPathToCstring(StringInfo out, JsonPath *in, int estimated_len)
{
	StringInfoData buf;
	JsonPathItem v;

	if (!out)
	{
		out = &buf;
		initStringInfo(out);
	}
	enlargeStringInfo(out, estimated_len);

	if (!(in->header & JSONPATH_LAX))
		appendBinaryStringInfo(out, "strict ", 7);

	jspInit(&v, in);
	printJsonPathItem(out, &v, false, true);

	return out->data;
}