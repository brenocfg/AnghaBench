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
typedef  enum path_delim { ____Placeholder_path_delim } path_delim ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ Point ;

/* Variables and functions */
 int /*<<< orphan*/  DELIM ; 
 int /*<<< orphan*/  LDELIM ; 
 int /*<<< orphan*/  LDELIM_EP ; 
#define  PATH_CLOSED 130 
#define  PATH_NONE 129 
#define  PATH_OPEN 128 
 int /*<<< orphan*/  RDELIM ; 
 int /*<<< orphan*/  RDELIM_EP ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pair_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static char *
path_encode(enum path_delim path_delim, int npts, Point *pt)
{
	StringInfoData str;
	int			i;

	initStringInfo(&str);

	switch (path_delim)
	{
		case PATH_CLOSED:
			appendStringInfoChar(&str, LDELIM);
			break;
		case PATH_OPEN:
			appendStringInfoChar(&str, LDELIM_EP);
			break;
		case PATH_NONE:
			break;
	}

	for (i = 0; i < npts; i++)
	{
		if (i > 0)
			appendStringInfoChar(&str, DELIM);
		appendStringInfoChar(&str, LDELIM);
		pair_encode(pt->x, pt->y, &str);
		appendStringInfoChar(&str, RDELIM);
		pt++;
	}

	switch (path_delim)
	{
		case PATH_CLOSED:
			appendStringInfoChar(&str, RDELIM);
			break;
		case PATH_OPEN:
			appendStringInfoChar(&str, RDELIM_EP);
			break;
		case PATH_NONE:
			break;
	}

	return str.data;
}