#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  PATH_MAX ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 char* d_absolute_path (struct path const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *ima_d_path(const struct path *path, char **pathbuf, char *namebuf)
{
	char *pathname = NULL;

	*pathbuf = __getname();
	if (*pathbuf) {
		pathname = d_absolute_path(path, *pathbuf, PATH_MAX);
		if (IS_ERR(pathname)) {
			__putname(*pathbuf);
			*pathbuf = NULL;
			pathname = NULL;
		}
	}

	if (!pathname) {
		strlcpy(namebuf, path->dentry->d_name.name, NAME_MAX);
		pathname = namebuf;
	}

	return pathname;
}