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
struct string_list {int /*<<< orphan*/ * next; int /*<<< orphan*/  tag; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_NORMAL ; 
 struct string_list* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct string_list *mk_node(const char *string)
{
	struct string_list *newnode;

	newnode = xmalloc(sizeof(*newnode));
	newnode->string = xstrdup(string);
	newnode->tag = SYM_NORMAL;
	newnode->next = NULL;

	return newnode;
}