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
struct dirent {char* d_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int installable; int /*<<< orphan*/  reachable; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ ExtensionVersionInfo ;
typedef  TYPE_2__ ExtensionControlFile ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* get_ext_ver_info (char*,int /*<<< orphan*/ **) ; 
 char* get_extension_script_directory (TYPE_2__*) ; 
 int /*<<< orphan*/  is_extension_script_filename (char*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* pstrdup (char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static List *
get_ext_ver_list(ExtensionControlFile *control)
{
	List	   *evi_list = NIL;
	int			extnamelen = strlen(control->name);
	char	   *location;
	DIR		   *dir;
	struct dirent *de;

	location = get_extension_script_directory(control);
	dir = AllocateDir(location);
	while ((de = ReadDir(dir, location)) != NULL)
	{
		char	   *vername;
		char	   *vername2;
		ExtensionVersionInfo *evi;
		ExtensionVersionInfo *evi2;

		/* must be a .sql file ... */
		if (!is_extension_script_filename(de->d_name))
			continue;

		/* ... matching extension name followed by separator */
		if (strncmp(de->d_name, control->name, extnamelen) != 0 ||
			de->d_name[extnamelen] != '-' ||
			de->d_name[extnamelen + 1] != '-')
			continue;

		/* extract version name(s) from 'extname--something.sql' filename */
		vername = pstrdup(de->d_name + extnamelen + 2);
		*strrchr(vername, '.') = '\0';
		vername2 = strstr(vername, "--");
		if (!vername2)
		{
			/* It's an install, not update, script; record its version name */
			evi = get_ext_ver_info(vername, &evi_list);
			evi->installable = true;
			continue;
		}
		*vername2 = '\0';		/* terminate first version */
		vername2 += 2;			/* and point to second */

		/* if there's a third --, it's bogus, ignore it */
		if (strstr(vername2, "--"))
			continue;

		/* Create ExtensionVersionInfos and link them together */
		evi = get_ext_ver_info(vername, &evi_list);
		evi2 = get_ext_ver_info(vername2, &evi_list);
		evi->reachable = lappend(evi->reachable, evi2);
	}
	FreeDir(dir);

	return evi_list;
}