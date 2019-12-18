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
struct strlist_config {char const* dirname; int file_only; } ;
struct strlist {int dummy; } ;
struct str_node {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int random () ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 struct str_node* strlist__entry (struct strlist*,int) ; 
 struct strlist* strlist__new (char*,struct strlist_config*) ; 
 int strlist__nr_entries (struct strlist*) ; 

const char *perf_tip(const char *dirpath)
{
	struct strlist *tips;
	struct str_node *node;
	char *tip = NULL;
	struct strlist_config conf = {
		.dirname = dirpath,
		.file_only = true,
	};

	tips = strlist__new("tips.txt", &conf);
	if (tips == NULL)
		return errno == ENOENT ? NULL :
			"Tip: check path of tips.txt or get more memory! ;-p";

	if (strlist__nr_entries(tips) == 0)
		goto out;

	node = strlist__entry(tips, random() % strlist__nr_entries(tips));
	if (asprintf(&tip, "Tip: %s", node->s) < 0)
		tip = (char *)"Tip: get more memory! ;-)";

out:
	strlist__delete(tips);

	return tip;
}