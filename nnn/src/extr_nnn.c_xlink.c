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

/* Variables and functions */
 size_t NONE_SELECTED ; 
 size_t PATH_MAX ; 
 int /*<<< orphan*/  endselection () ; 
 int link (char const*,char const*) ; 
 char** messages ; 
 size_t mkpath (char*,char*,char*) ; 
 int /*<<< orphan*/  printwait (char*,int*) ; 
 char* pselbuf ; 
 size_t selbufpos ; 
 size_t strlen (char*) ; 
 int symlink (char const*,char const*) ; 
 char* xbasename (char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int xlink(char *suffix, char *path, char *buf, int *presel, int type)
{
	int count = 0;
	char *pbuf = pselbuf, *fname;
	size_t pos = 0, len, r;
	int (*link_fn)(const char *, const char *) = NULL;

	/* Check if selection is empty */
	if (!selbufpos) {
		printwait(messages[NONE_SELECTED], presel);
		return -1;
	}

	endselection();

	if (type == 's') /* symbolic link */
		link_fn = &symlink;
	else /* hard link */
		link_fn = &link;

	while (pos < selbufpos) {
		len = strlen(pbuf);
		fname = xbasename(pbuf);
		r = mkpath(path, fname, buf);
		xstrlcpy(buf + r - 1, suffix, PATH_MAX - r - 1);

		if (!link_fn(pbuf, buf))
			++count;

		pos += len + 1;
		pbuf += len + 1;
	}

	if (!count)
		printwait("none created", presel);

	return count;
}