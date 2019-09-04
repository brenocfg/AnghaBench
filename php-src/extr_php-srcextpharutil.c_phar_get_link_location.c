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
struct TYPE_3__ {char* link; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ phar_entry_info ;

/* Variables and functions */
 char* estrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static char *phar_get_link_location(phar_entry_info *entry) /* {{{ */
{
	char *p, *ret = NULL;
	if (!entry->link) {
		return NULL;
	}
	if (entry->link[0] == '/') {
		return estrdup(entry->link + 1);
	}
	p = strrchr(entry->filename, '/');
	if (p) {
		*p = '\0';
		spprintf(&ret, 0, "%s/%s", entry->filename, entry->link);
		return ret;
	}
	return entry->link;
}