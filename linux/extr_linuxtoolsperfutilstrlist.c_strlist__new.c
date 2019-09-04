#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strlist_config {char* dirname; int file_only; int /*<<< orphan*/  dont_dupstr; } ;
struct TYPE_2__ {int /*<<< orphan*/  node_delete; int /*<<< orphan*/  node_new; int /*<<< orphan*/  node_cmp; } ;
struct strlist {int dupstr; int file_only; TYPE_1__ rblist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct strlist*) ; 
 struct strlist* malloc (int) ; 
 int /*<<< orphan*/  rblist__init (TYPE_1__*) ; 
 int /*<<< orphan*/  strlist__node_cmp ; 
 int /*<<< orphan*/  strlist__node_delete ; 
 int /*<<< orphan*/  strlist__node_new ; 
 scalar_t__ strlist__parse_list (struct strlist*,char const*,char const*) ; 

struct strlist *strlist__new(const char *list, const struct strlist_config *config)
{
	struct strlist *slist = malloc(sizeof(*slist));

	if (slist != NULL) {
		bool dupstr = true;
		bool file_only = false;
		const char *dirname = NULL;

		if (config) {
			dupstr = !config->dont_dupstr;
			dirname = config->dirname;
			file_only = config->file_only;
		}

		rblist__init(&slist->rblist);
		slist->rblist.node_cmp    = strlist__node_cmp;
		slist->rblist.node_new    = strlist__node_new;
		slist->rblist.node_delete = strlist__node_delete;

		slist->dupstr	 = dupstr;
		slist->file_only = file_only;

		if (list && strlist__parse_list(slist, list, dirname) != 0)
			goto out_error;
	}

	return slist;
out_error:
	free(slist);
	return NULL;
}