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
struct mlist {struct mlist* prev; struct mlist* next; } ;
typedef  int /*<<< orphan*/  RMagic ;

/* Variables and functions */
 char* MAGICFILE ; 
 int /*<<< orphan*/  PATHSEP ; 
 int /*<<< orphan*/  R_FREE (struct mlist*) ; 
 int R_MAX (int,int) ; 
 int apprentice_1 (int /*<<< orphan*/ *,char const*,int,struct mlist*) ; 
 int /*<<< orphan*/  file_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  file_oomem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  init_file_tables () ; 
 struct mlist* malloc (int) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

struct mlist * file_apprentice(RMagic *ms, const char *fn, int action) {
	char *p, *mfn;
	int file_err, errs = -1;
	struct mlist *mlist;

	init_file_tables ();

	if (!fn) {
		fn = getenv ("MAGIC");
	}
	if (!fn) {
		fn = MAGICFILE;
	}

	if (!(mfn = strdup (fn))) {
		file_oomem (ms, strlen (fn));
		return NULL;
	}
	fn = mfn;

	if (!(mlist = malloc (sizeof (*mlist)))) {
		free (mfn);
		file_oomem (ms, sizeof (*mlist));
		return NULL;
	}
	mlist->next = mlist->prev = mlist;

	while (fn) {
		p = strchr (fn, PATHSEP);
		if (p) {
			*p++ = '\0';
		}
		if (*fn == '\0') {
			break;
		}
		file_err = apprentice_1 (ms, fn, action, mlist);
		errs = R_MAX (errs, file_err);
		fn = p;
	}
	if (errs == -1) {
		free (mfn);
		R_FREE (mlist);
		file_error (ms, 0, "could not find any magic files!");
		return NULL;
	}
	free (mfn);
	return mlist;
}