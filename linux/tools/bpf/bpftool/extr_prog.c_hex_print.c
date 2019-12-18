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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void hex_print(void *data, unsigned int size, FILE *f)
{
	size_t i, j;
	char c;

	for (i = 0; i < size; i += 16) {
		/* Row offset */
		fprintf(f, "%07zx\t", i);

		/* Hexadecimal values */
		for (j = i; j < i + 16 && j < size; j++)
			fprintf(f, "%02x%s", *(uint8_t *)(data + j),
				j % 2 ? " " : "");
		for (; j < i + 16; j++)
			fprintf(f, "  %s", j % 2 ? " " : "");

		/* ASCII values (if relevant), '.' otherwise */
		fprintf(f, "| ");
		for (j = i; j < i + 16 && j < size; j++) {
			c = *(char *)(data + j);
			if (c < ' ' || c > '~')
				c = '.';
			fprintf(f, "%c%s", c, j == i + 7 ? " " : "");
		}

		fprintf(f, "\n");
	}
}