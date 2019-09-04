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
struct string_list {char* string; size_t tag; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {scalar_t__ n; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EOF ; 
 size_t SYM_NORMAL ; 
 struct string_list* copy_node (struct string_list*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* symbol_types ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct string_list *read_node(FILE *f)
{
	char buffer[256];
	struct string_list node = {
		.string = buffer,
		.tag = SYM_NORMAL };
	int c, in_string = 0;

	while ((c = fgetc(f)) != EOF) {
		if (!in_string && c == ' ') {
			if (node.string == buffer)
				continue;
			break;
		} else if (c == '"') {
			in_string = !in_string;
		} else if (c == '\n') {
			if (node.string == buffer)
				return NULL;
			ungetc(c, f);
			break;
		}
		if (node.string >= buffer + sizeof(buffer) - 1) {
			fprintf(stderr, "Token too long\n");
			exit(1);
		}
		*node.string++ = c;
	}
	if (node.string == buffer)
		return NULL;
	*node.string = 0;
	node.string = buffer;

	if (node.string[1] == '#') {
		size_t n;

		for (n = 0; n < ARRAY_SIZE(symbol_types); n++) {
			if (node.string[0] == symbol_types[n].n) {
				node.tag = n;
				node.string += 2;
				return copy_node(&node);
			}
		}
		fprintf(stderr, "Unknown type %c\n", node.string[0]);
		exit(1);
	}
	return copy_node(&node);
}