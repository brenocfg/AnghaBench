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
struct string_list {struct string_list* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct string_list** alloca (int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_list(FILE * f, struct string_list *list)
{
	struct string_list **e, **b;
	struct string_list *tmp, **tmp2;
	int elem = 1;

	if (list == NULL) {
		fputs("(nil)", f);
		return;
	}

	tmp = list;
	while ((tmp = tmp->next) != NULL)
		elem++;

	b = alloca(elem * sizeof(*e));
	e = b + elem;
	tmp2 = e - 1;

	(*tmp2--) = list;
	while ((list = list->next) != NULL)
		*(tmp2--) = list;

	while (b != e) {
		print_node(f, *b++);
		putc(' ', f);
	}
}