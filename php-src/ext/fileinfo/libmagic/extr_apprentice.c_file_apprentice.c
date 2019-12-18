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
struct magic_set {int /*<<< orphan*/ ** mlist; } ;

/* Variables and functions */
#define  FILE_CHECK 131 
#define  FILE_COMPILE 130 
#define  FILE_LIST 129 
#define  FILE_LOAD 128 
 size_t MAGIC_SETS ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  PATHSEP ; 
 int apprentice_1 (struct magic_set*,char const*,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  file_error (struct magic_set*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  file_oomem (struct magic_set*,int) ; 
 int /*<<< orphan*/  file_reset (struct magic_set*,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  init_file_tables () ; 
 char* magic_getpath (char const*,int) ; 
 void* mlist_alloc () ; 
 int /*<<< orphan*/  mlist_free (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int
file_apprentice(struct magic_set *ms, const char *fn, int action)
{
	char *p, *mfn;
	int fileerr, errs = -1;
	size_t i;

	(void)file_reset(ms, 0);

/* XXX disabling default magic loading so the compiled in data is used */
#if 0
	if ((fn = magic_getpath(fn, action)) == NULL)
		return -1;
#endif

	init_file_tables();

	if (fn == NULL)
		fn = getenv("MAGIC");
	if (fn == NULL) {
		for (i = 0; i < MAGIC_SETS; i++) {
			mlist_free(ms->mlist[i]);
			if ((ms->mlist[i] = mlist_alloc()) == NULL) {
				file_oomem(ms, sizeof(*ms->mlist[i]));
				return -1;
			}
		}
		return apprentice_1(ms, fn, action);
	}

	if ((mfn = estrdup(fn)) == NULL) {
		file_oomem(ms, strlen(fn));
		return -1;
	}

	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		if ((ms->mlist[i] = mlist_alloc()) == NULL) {
			file_oomem(ms, sizeof(*ms->mlist[i]));
			while (i-- > 0) {
				mlist_free(ms->mlist[i]);
				ms->mlist[i] = NULL;
			}
			efree(mfn);
			return -1;
		}
	}
	fn = mfn;

	while (fn) {
		p = strchr(fn, PATHSEP);
		if (p)
			*p++ = '\0';
		if (*fn == '\0')
			break;
		fileerr = apprentice_1(ms, fn, action);
		errs = MAX(errs, fileerr);
		fn = p;
	}

	efree(mfn);

	if (errs == -1) {
		for (i = 0; i < MAGIC_SETS; i++) {
			mlist_free(ms->mlist[i]);
			ms->mlist[i] = NULL;
		}
		file_error(ms, 0, "could not find any valid magic files!");
		return -1;
	}

#if 0
	/*
	 * Always leave the database loaded
	 */
	if (action == FILE_LOAD)
		return 0;

	for (i = 0; i < MAGIC_SETS; i++) {
		mlist_free(ms->mlist[i]);
		ms->mlist[i] = NULL;
	}
#endif

	switch (action) {
	case FILE_LOAD:
	case FILE_COMPILE:
	case FILE_CHECK:
	case FILE_LIST:
		return 0;
	default:
		file_error(ms, 0, "Invalid action %d", action);
		return -1;
	}
}