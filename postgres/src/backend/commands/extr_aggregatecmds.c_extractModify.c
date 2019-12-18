#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defname; } ;
typedef  TYPE_1__ DefElem ;

/* Variables and functions */
 char AGGMODIFY_READ_ONLY ; 
 char AGGMODIFY_READ_WRITE ; 
 char AGGMODIFY_SHAREABLE ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char* defGetString (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static char
extractModify(DefElem *defel)
{
	char	   *val = defGetString(defel);

	if (strcmp(val, "read_only") == 0)
		return AGGMODIFY_READ_ONLY;
	if (strcmp(val, "shareable") == 0)
		return AGGMODIFY_SHAREABLE;
	if (strcmp(val, "read_write") == 0)
		return AGGMODIFY_READ_WRITE;
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("parameter \"%s\" must be READ_ONLY, SHAREABLE, or READ_WRITE",
					defel->defname)));
	return 0;					/* keep compiler quiet */
}