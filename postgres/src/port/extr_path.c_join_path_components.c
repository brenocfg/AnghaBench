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
 scalar_t__ IS_DIR_SEP (char const) ; 
 int MAXPGPATH ; 
 char* skip_drive (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 

void
join_path_components(char *ret_path,
					 const char *head, const char *tail)
{
	if (ret_path != head)
		strlcpy(ret_path, head, MAXPGPATH);

	/*
	 * Remove any leading "." in the tail component.
	 *
	 * Note: we used to try to remove ".." as well, but that's tricky to get
	 * right; now we just leave it to be done by canonicalize_path() later.
	 */
	while (tail[0] == '.' && IS_DIR_SEP(tail[1]))
		tail += 2;

	if (*tail)
	{
		/* only separate with slash if head wasn't empty */
		snprintf(ret_path + strlen(ret_path), MAXPGPATH - strlen(ret_path),
				 "%s%s",
				 (*(skip_drive(head)) != '\0') ? "/" : "",
				 tail);
	}
}