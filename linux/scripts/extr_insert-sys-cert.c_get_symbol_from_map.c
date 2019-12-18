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
struct sym {int offset; char* name; void* content; int /*<<< orphan*/  address; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LINE_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_offset_from_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void get_symbol_from_map(Elf_Ehdr *hdr, FILE *f, char *name,
				struct sym *s)
{
	char l[LINE_SIZE];
	char *w, *p, *n;

	s->size = 0;
	s->address = 0;
	s->offset = 0;
	if (fseek(f, 0, SEEK_SET) != 0) {
		perror("File seek failed");
		exit(EXIT_FAILURE);
	}
	while (fgets(l, LINE_SIZE, f)) {
		p = strchr(l, '\n');
		if (!p) {
			err("Missing line ending.\n");
			return;
		}
		n = strstr(l, name);
		if (n)
			break;
	}
	if (!n) {
		err("Unable to find symbol: %s\n", name);
		return;
	}
	w = strchr(l, ' ');
	if (!w)
		return;

	*w = '\0';
	s->address = strtoul(l, NULL, 16);
	if (s->address == 0)
		return;
	s->offset = get_offset_from_address(hdr, s->address);
	s->name = name;
	s->content = (void *)hdr + s->offset;
}