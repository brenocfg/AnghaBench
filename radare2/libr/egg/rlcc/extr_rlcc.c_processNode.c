#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int children_num; char* tag; char* contents; struct TYPE_8__** children; } ;
typedef  TYPE_1__ mpc_ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isComment (TYPE_1__*) ; 
 scalar_t__ isInlineAssembly (TYPE_1__*) ; 
 scalar_t__ isProcedure (TYPE_1__*) ; 
 scalar_t__ isSigdef (TYPE_1__*) ; 
 scalar_t__ isStatement (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void processNode (mpc_ast_t *node) {
	if (isStatement(node)) {
		int i, narg = 0;
		const char *args[32];
		for (i=0 ; i<node->children_num; i++) {
			const char *tag = node->children[i]->tag;
			const char *val = node->children[i]->contents;
			if (strcmp (tag, "char")) {
				printf ("TAG (%s) = (%s)\n", tag, val);
				args[narg++] = val;
			}
		}
		printf ("; CALL WITH %d ARGS\n", narg);
	} else if (isProcedure (node)) {
		int i, j;
		const char *name = node->children[0]->contents;
		printf ("%s:\n", name);
		for (i=0 ; i<node->children_num; i++) {
			if (!strcmp (node->children[i]->tag, "body|>")) {
				node = node->children[i];
				for (i=0 ; i<node->children_num; i++) {
					if (!strcmp (node->children[i]->tag, "stmt|>")) {
						processNode (node->children[i]);
					} else {
						eprintf ("UNK %s\n", node->children[i]->tag);
					}
				}
				break;
			}
		}
	} else if (isSigdef (node)) {
		if (node->children_num>4) {
			const char *name = node->children[0]->contents;
			const char *type = node->children[2]->contents;
			const char *size = node->children[4]->contents;
			if (!strcmp (type, "alias")) {
				printf (".equ %s,%s\n", name, size);
			} else if (!strcmp (type, "syscall")) {
				printf ("; TODO: register syscall %s number %s\n", name, size);
			} else if (!strcmp (type, "global")) {
				printf ("; TODO: global \n");
			} else {
				printf ("; UNKNOWN EXPRESISON: NAME = '%s' ", name);
				printf ("TYPE = '%s' ", type);
				printf ("SIZE = '%s'\n", size);
			}
		}
	} else if (isComment (node)) {
		char *s = strdup (node->contents + 2);
		int len = strlen (s);
		if (node->contents[1] == '*') {
			s[len-2] = 0;
		}
		while (s) {
			char *nl = strchr (s, '\n');
			if (nl) {
				*nl = 0;
				printf ("; %s\n", s);
				s = nl + 1;
			} else {
				printf ("; %s\n", s);
				s = NULL;
			}
		}
		free (s);
	} else if (isInlineAssembly (node)) {
		printf ("%s\n", node->contents+1);
	}
}