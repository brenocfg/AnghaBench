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
struct strlist {int dummy; } ;
struct strfilter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int probe_file__del_strlist (int,struct strlist*) ; 
 int probe_file__get_events (int,struct strfilter*,struct strlist*) ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 struct strlist* strlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int probe_file__del_events(int fd, struct strfilter *filter)
{
	struct strlist *namelist;
	int ret;

	namelist = strlist__new(NULL, NULL);
	if (!namelist)
		return -ENOMEM;

	ret = probe_file__get_events(fd, filter, namelist);
	if (ret < 0)
		return ret;

	ret = probe_file__del_strlist(fd, namelist);
	strlist__delete(namelist);

	return ret;
}