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
struct strlist {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_CMDLEN ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int strlen (char*) ; 
 int strlist__add (struct strlist*,char*) ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 struct strlist* strlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct strlist *probe_file__get_rawlist(int fd)
{
	int ret, idx, fddup;
	FILE *fp;
	char buf[MAX_CMDLEN];
	char *p;
	struct strlist *sl;

	if (fd < 0)
		return NULL;

	sl = strlist__new(NULL, NULL);
	if (sl == NULL)
		return NULL;

	fddup = dup(fd);
	if (fddup < 0)
		goto out_free_sl;

	fp = fdopen(fddup, "r");
	if (!fp)
		goto out_close_fddup;

	while (!feof(fp)) {
		p = fgets(buf, MAX_CMDLEN, fp);
		if (!p)
			break;

		idx = strlen(p) - 1;
		if (p[idx] == '\n')
			p[idx] = '\0';
		ret = strlist__add(sl, buf);
		if (ret < 0) {
			pr_debug("strlist__add failed (%d)\n", ret);
			goto out_close_fp;
		}
	}
	fclose(fp);

	return sl;

out_close_fp:
	fclose(fp);
	goto out_free_sl;
out_close_fddup:
	close(fddup);
out_free_sl:
	strlist__delete(sl);
	return NULL;
}