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
struct symbol {int flags; } ;
struct menu {struct symbol* sym; struct menu* next; struct menu* list; } ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  COL_MENU ; 
 scalar_t__ OPT_ALL ; 
 scalar_t__ OPT_NORMAL ; 
 scalar_t__ OPT_PROMPT ; 
 int SYMBOL_CHANGED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  fill_row (struct menu*) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct menu**,int) ; 
 scalar_t__ gtk_tree_model_iter_children (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_tree_model_iter_next (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_insert_before (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtktree_iter_find_node (int /*<<< orphan*/ *,struct menu*) ; 
 int indent ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_get_prompt (struct menu*) ; 
 int /*<<< orphan*/  menu_has_prompt (struct menu*) ; 
 int /*<<< orphan*/  menu_is_visible (struct menu*) ; 
 int /*<<< orphan*/  model2 ; 
 scalar_t__ opt_mode ; 
 struct menu rootmenu ; 
 int /*<<< orphan*/  set_node (int /*<<< orphan*/ *,struct menu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree2 ; 

__attribute__((used)) static void update_tree(struct menu *src, GtkTreeIter * dst)
{
	struct menu *child1;
	GtkTreeIter iter, tmp;
	GtkTreeIter *child2 = &iter;
	gboolean valid;
	GtkTreeIter *sibling;
	struct symbol *sym;
	struct menu *menu1, *menu2;

	if (src == &rootmenu)
		indent = 1;

	valid = gtk_tree_model_iter_children(model2, child2, dst);
	for (child1 = src->list; child1; child1 = child1->next) {

		sym = child1->sym;

	      reparse:
		menu1 = child1;
		if (valid)
			gtk_tree_model_get(model2, child2, COL_MENU,
					   &menu2, -1);
		else
			menu2 = NULL;	// force adding of a first child

#ifdef DEBUG
		printf("%*c%s | %s\n", indent, ' ',
		       menu1 ? menu_get_prompt(menu1) : "nil",
		       menu2 ? menu_get_prompt(menu2) : "nil");
#endif

		if ((opt_mode == OPT_NORMAL && !menu_is_visible(child1)) ||
		    (opt_mode == OPT_PROMPT && !menu_has_prompt(child1)) ||
		    (opt_mode == OPT_ALL    && !menu_get_prompt(child1))) {

			/* remove node */
			if (gtktree_iter_find_node(dst, menu1) != NULL) {
				memcpy(&tmp, child2, sizeof(GtkTreeIter));
				valid = gtk_tree_model_iter_next(model2,
								 child2);
				gtk_tree_store_remove(tree2, &tmp);
				if (!valid)
					return;		/* next parent */
				else
					goto reparse;	/* next child */
			} else
				continue;
		}

		if (menu1 != menu2) {
			if (gtktree_iter_find_node(dst, menu1) == NULL) {	// add node
				if (!valid && !menu2)
					sibling = NULL;
				else
					sibling = child2;
				gtk_tree_store_insert_before(tree2,
							     child2,
							     dst, sibling);
				set_node(child2, menu1, fill_row(menu1));
				if (menu2 == NULL)
					valid = TRUE;
			} else {	// remove node
				memcpy(&tmp, child2, sizeof(GtkTreeIter));
				valid = gtk_tree_model_iter_next(model2,
								 child2);
				gtk_tree_store_remove(tree2, &tmp);
				if (!valid)
					return;	// next parent
				else
					goto reparse;	// next child
			}
		} else if (sym && (sym->flags & SYMBOL_CHANGED)) {
			set_node(child2, menu1, fill_row(menu1));
		}

		indent++;
		update_tree(child1, child2);
		indent--;

		valid = gtk_tree_model_iter_next(model2, child2);
	}
}