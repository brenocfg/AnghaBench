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
struct TYPE_3__ {char* directory; } ;
typedef  TYPE_1__ ExtensionControlFile ;

/* Variables and functions */
 int MAXPGPATH ; 
 char* get_extension_control_directory () ; 
 int /*<<< orphan*/  get_share_path (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_absolute_path (char*) ; 
 int /*<<< orphan*/  my_exec_path ; 
 scalar_t__ palloc (int) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static char *
get_extension_script_directory(ExtensionControlFile *control)
{
	char		sharepath[MAXPGPATH];
	char	   *result;

	/*
	 * The directory parameter can be omitted, absolute, or relative to the
	 * installation's share directory.
	 */
	if (!control->directory)
		return get_extension_control_directory();

	if (is_absolute_path(control->directory))
		return pstrdup(control->directory);

	get_share_path(my_exec_path, sharepath);
	result = (char *) palloc(MAXPGPATH);
	snprintf(result, MAXPGPATH, "%s/%s", sharepath, control->directory);

	return result;
}