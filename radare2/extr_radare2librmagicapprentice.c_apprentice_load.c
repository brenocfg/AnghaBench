#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut32 ;
typedef  int /*<<< orphan*/  subfn ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct r_magic_entry {scalar_t__ cont_level; char* mimetype; char* desc; int flag; scalar_t__ type; size_t cont_count; struct r_magic_entry* mp; int /*<<< orphan*/  lineno; } ;
struct r_magic {int dummy; } ;
struct dirent {char* d_name; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ RMagic ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int BINTEST ; 
 int FILE_CHECK ; 
 scalar_t__ FILE_DEFAULT ; 
 int MAXMAGIS ; 
 int MAXPATHLEN ; 
 int MAXstring ; 
 int R_MAGIC_CHECK ; 
 int R_MAGIC_DEBUG ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apprentice_sort ; 
 struct r_magic_entry* calloc (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_magwarn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  file_oomem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct r_magic_entry*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  load_1 (TYPE_1__*,int,char const*,int*,struct r_magic_entry**,size_t*) ; 
 struct r_magic* malloc (int) ; 
 int maxmagic ; 
 int /*<<< orphan*/  memcpy (struct r_magic*,struct r_magic_entry*,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  qsort (struct r_magic_entry*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sandbox_check_path (char const*) ; 
 scalar_t__ r_sandbox_enable (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_test_type (struct r_magic_entry*,struct r_magic_entry*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  usg_hdr ; 

__attribute__((used)) static int apprentice_load(RMagic *ms, struct r_magic **magicp, ut32 *nmagicp, const char *fn, int action) {
	ut32 marraycount, i, mentrycount = 0, starttest;
	struct r_magic_entry *marray;
	struct stat st;
	int errs = 0;
#if !__WINDOWS__
	DIR *dir;
	struct dirent *d;
	char subfn[MAXPATHLEN];
#else	
	HANDLE hdir;
	WIN32_FIND_DATAW entry;
	wchar_t dir[MAX_PATH];
	wchar_t *wcpath;
	char *cfname;
	char subfn[1024];	
#endif
	ms->flags |= R_MAGIC_CHECK;	/* Enable checks for parsed files */

        maxmagic = MAXMAGIS;
	if (!(marray = calloc (maxmagic, sizeof (*marray)))) {
		file_oomem (ms, maxmagic * sizeof (*marray));
		return -1;
	}
	marraycount = 0;

	/* print silly verbose header for USG compat. */
	if (action == FILE_CHECK) {
		eprintf ("%s\n", usg_hdr);
	}

	/* load directory or file */
	if (stat (fn, &st) == 0 && S_ISDIR (st.st_mode)) {
		if (r_sandbox_enable (0) && !r_sandbox_check_path (fn)) {
			free (marray);
			return  -1;
		}
#if __WINDOWS__ && !defined(__CYGWIN__)
		if ((wcpath = r_utf8_to_utf16 (fn))) {
			swprintf (dir, _countof (dir), L"%ls\\*.*", wcpath);
			hdir = FindFirstFileW (dir, &entry);
			if (!(hdir == INVALID_HANDLE_VALUE)) {
				do {
					if (wcsncmp (entry.cFileName, L".", 1) == 0) continue;
					if ((cfname = r_utf16_to_utf8 (entry.cFileName))) {
						snprintf (subfn, sizeof (subfn), "%s/%s", fn, cfname);
						if (stat (subfn, &st) == 0 && S_ISREG (st.st_mode)) {
							load_1 (ms, action, subfn, &errs, &marray, &marraycount);
						}
						free (cfname);
					}
				} while (FindNextFileW (hdir, &entry));
				FindClose (hdir);
			}
			free (wcpath);
		} else {
			errs++;
		}
#else
		dir = opendir (fn);
		if (dir) {
			while ((d = readdir (dir))) {
				if (*d->d_name == '.') {
					continue;
				}
				snprintf (subfn, sizeof (subfn), "%s/%s", fn, d->d_name);
				if (stat (subfn, &st) == 0 && S_ISREG (st.st_mode)) {
					load_1 (ms, action, subfn, &errs, &marray, &marraycount);
				}
				//else perror (subfn);
			}
			closedir (dir);
		} else {
			errs++;
		}
#endif
	} else {
		load_1 (ms, action, fn, &errs, &marray, &marraycount);
	}
	if (errs) {
		goto out;
	}

	/* Set types of tests */
	for (i = 0; i < marraycount; ) {
		if (marray[i].mp->cont_level != 0) {
			i++;
			continue;
		}

		starttest = i;
		do {
			set_test_type(marray[starttest].mp, marray[i].mp);
			if (ms->flags & R_MAGIC_DEBUG) {
				(void)fprintf(stderr, "%s%s%s: %s\n",
					marray[i].mp->mimetype,
					marray[i].mp->mimetype[0] == '\0' ? "" : "; ",
					marray[i].mp->desc[0] ? marray[i].mp->desc : "(no description)",
					marray[i].mp->flag & BINTEST ? "binary" : "text");
				if (marray[i].mp->flag & BINTEST) {
#define SYMBOL "text"
#define SYMLEN sizeof (SYMBOL)
					char *p = strstr(marray[i].mp->desc, "text");
					if (p && (p == marray[i].mp->desc || isspace((unsigned char)p[-1])) &&
					    (p + SYMLEN - marray[i].mp->desc == MAXstring ||
					     (p[SYMLEN] == '\0' || isspace((unsigned char)p[SYMLEN])))) {
						(void)fprintf(stderr,
							      "*** Possible binary test for text type\n");
					}
#undef SYMBOL
#undef SYMLEN
				}
			}
		} while (++i < marraycount && marray[i].mp->cont_level != 0);
	}

	qsort (marray, marraycount, sizeof (*marray), apprentice_sort);

	/*
	 * Make sure that any level 0 "default" line is last (if one exists).
	 */
	for (i = 0; i < marraycount; i++) {
		if (marray[i].mp->cont_level == 0 &&
		    marray[i].mp->type == FILE_DEFAULT) {
			while (++i < marraycount) {
				if (marray[i].mp->cont_level == 0) {
					break;
				}
			}
			if (i != marraycount) {
				ms->line = marray[i].mp->lineno; /* XXX - Ugh! */
				file_magwarn (ms, "level 0 \"default\" did not sort last");
			}
			break;
		}
	}

	for (i = 0; i < marraycount; i++) {
		mentrycount += marray[i].cont_count;
	}

	if (!(*magicp = malloc (1 + (sizeof (**magicp) * mentrycount)))) {
		file_oomem (ms, sizeof (**magicp) * mentrycount);
		errs++;
		goto out;
	}

	mentrycount = 0;
	for (i = 0; i < marraycount; i++) {
		(void)memcpy (*magicp + mentrycount, marray[i].mp,
		    marray[i].cont_count * sizeof (**magicp));
		mentrycount += marray[i].cont_count;
	}
out:
	for (i = 0; i < marraycount; i++) {
		free (marray[i].mp);
	}
	free (marray);
	if (errs) {
		*magicp = NULL;
		*nmagicp = 0;
		return errs;
	}
	*nmagicp = mentrycount;
	return 0;
}