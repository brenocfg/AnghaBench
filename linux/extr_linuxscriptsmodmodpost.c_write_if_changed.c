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
struct stat {int /*<<< orphan*/  st_size; } ;
struct buffer {int /*<<< orphan*/  pos; int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* NOFAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 

__attribute__((used)) static void write_if_changed(struct buffer *b, const char *fname)
{
	char *tmp;
	FILE *file;
	struct stat st;

	file = fopen(fname, "r");
	if (!file)
		goto write;

	if (fstat(fileno(file), &st) < 0)
		goto close_write;

	if (st.st_size != b->pos)
		goto close_write;

	tmp = NOFAIL(malloc(b->pos));
	if (fread(tmp, 1, b->pos, file) != b->pos)
		goto free_write;

	if (memcmp(tmp, b->p, b->pos) != 0)
		goto free_write;

	free(tmp);
	fclose(file);
	return;

 free_write:
	free(tmp);
 close_write:
	fclose(file);
 write:
	file = fopen(fname, "w");
	if (!file) {
		perror(fname);
		exit(1);
	}
	if (fwrite(b->p, 1, b->pos, file) != b->pos) {
		perror(fname);
		exit(1);
	}
	fclose(file);
}