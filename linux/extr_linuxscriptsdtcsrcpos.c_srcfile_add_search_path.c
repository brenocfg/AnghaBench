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
struct search_path {struct search_path* next; int /*<<< orphan*/  dirname; } ;

/* Variables and functions */
 struct search_path* search_path_head ; 
 struct search_path** search_path_tail ; 
 struct search_path* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void srcfile_add_search_path(const char *dirname)
{
	struct search_path *node;

	/* Create the node */
	node = xmalloc(sizeof(*node));
	node->next = NULL;
	node->dirname = xstrdup(dirname);

	/* Add to the end of our list */
	if (search_path_tail)
		*search_path_tail = node;
	else
		search_path_head = node;
	search_path_tail = &node->next;
}