#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  HbaFileName ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int,char const*,int) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
verify_option_list_length(List *options, const char *optionname, List *masters, const char *mastername, int line_num)
{
	if (list_length(options) == 0 ||
		list_length(options) == 1 ||
		list_length(options) == list_length(masters))
		return true;

	ereport(LOG,
			(errcode(ERRCODE_CONFIG_FILE_ERROR),
			 errmsg("the number of %s (%d) must be 1 or the same as the number of %s (%d)",
					optionname,
					list_length(options),
					mastername,
					list_length(masters)
					),
			 errcontext("line %d of configuration file \"%s\"",
						line_num, HbaFileName)));
	return false;
}