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
struct strfilter_node {struct strfilter_node* r; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  root ;

/* Variables and functions */
 int /*<<< orphan*/ * OP_and ; 
 int /*<<< orphan*/ * OP_not ; 
 int /*<<< orphan*/ * OP_or ; 
 char* get_token (char const*,char const**) ; 
 int /*<<< orphan*/  memset (struct strfilter_node*,int /*<<< orphan*/ ,int) ; 
 void* strfilter_node__alloc (int /*<<< orphan*/ *,struct strfilter_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strfilter_node__delete (struct strfilter_node*) ; 
 int /*<<< orphan*/  strndup (char const*,int) ; 

__attribute__((used)) static struct strfilter_node *strfilter_node__new(const char *s,
						  const char **ep)
{
	struct strfilter_node root, *cur, *last_op;
	const char *e;

	if (!s)
		return NULL;

	memset(&root, 0, sizeof(root));
	last_op = cur = &root;

	s = get_token(s, &e);
	while (*s != '\0' && *s != ')') {
		switch (*s) {
		case '&':	/* Exchg last OP->r with AND */
			if (!cur->r || !last_op->r)
				goto error;
			cur = strfilter_node__alloc(OP_and, last_op->r, NULL);
			if (!cur)
				goto nomem;
			last_op->r = cur;
			last_op = cur;
			break;
		case '|':	/* Exchg the root with OR */
			if (!cur->r || !root.r)
				goto error;
			cur = strfilter_node__alloc(OP_or, root.r, NULL);
			if (!cur)
				goto nomem;
			root.r = cur;
			last_op = cur;
			break;
		case '!':	/* Add NOT as a leaf node */
			if (cur->r)
				goto error;
			cur->r = strfilter_node__alloc(OP_not, NULL, NULL);
			if (!cur->r)
				goto nomem;
			cur = cur->r;
			break;
		case '(':	/* Recursively parses inside the parenthesis */
			if (cur->r)
				goto error;
			cur->r = strfilter_node__new(s + 1, &s);
			if (!s)
				goto nomem;
			if (!cur->r || *s != ')')
				goto error;
			e = s + 1;
			break;
		default:
			if (cur->r)
				goto error;
			cur->r = strfilter_node__alloc(NULL, NULL, NULL);
			if (!cur->r)
				goto nomem;
			cur->r->p = strndup(s, e - s);
			if (!cur->r->p)
				goto nomem;
		}
		s = get_token(e, &e);
	}
	if (!cur->r)
		goto error;
	*ep = s;
	return root.r;
nomem:
	s = NULL;
error:
	*ep = s;
	strfilter_node__delete(root.r);
	return NULL;
}