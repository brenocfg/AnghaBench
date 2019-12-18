#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct stat {scalar_t__ st_atime; int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  fullpath ;
struct TYPE_7__ {int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
struct TYPE_8__ {float type; scalar_t__ time; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RFSRoot ;
typedef  TYPE_2__ RFSFile ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _countof (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 TYPE_2__* r_fs_file_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 char* r_utf16_to_utf8 (int /*<<< orphan*/ ) ; 
 char* r_utf8_to_utf16 (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  swprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static RList *fs_posix_dir(RFSRoot *root, const char *path, int view /*ignored*/) {
	RList *list;
	char fullpath[4096];
	struct stat st;
#if __WINDOWS__
	WIN32_FIND_DATAW entry;
	HANDLE fh;
	wchar_t *wcpath;
	char *wctocbuff;
	wchar_t directory[MAX_PATH];
#else
	struct dirent *de;
	DIR *dir;
#endif
	list = r_list_new ();
	if (!list) {
		return NULL;
	}
#if __WINDOWS__
	wcpath = r_utf8_to_utf16 (path);
	if (!wcpath) {
		return NULL;
	}
	swprintf (directory, _countof (directory), L"%ls\\*.*", wcpath);
	fh = FindFirstFileW (directory, &entry);
	if (fh == INVALID_HANDLE_VALUE) {
		free (wcpath);
		return NULL;
	}
	do {
		if ((wctocbuff = r_utf16_to_utf8 (entry.cFileName))) {
			RFSFile *fsf = r_fs_file_new (NULL, wctocbuff);
			if (!fsf) {
				r_list_free (list);
				FindClose (fh);
				return NULL;
			}
			fsf->type = 'f';
			snprintf (fullpath, sizeof (fullpath)-1, "%s/%s", path, wctocbuff);
			if (!stat (fullpath, &st)) {
				fsf->type = S_ISDIR (st.st_mode)?'d':'f';
				fsf->time = st.st_atime;
			} else {
				fsf->type = 'f';
				fsf->time = 0;
			}
			r_list_append (list, fsf);
			free (wctocbuff);
		}

	} while (FindNextFileW (fh, &entry));
	FindClose (fh);
#else
	dir = opendir (path);
	if (!dir) {
		r_list_free (list);
		return NULL;
	}
	while ((de = readdir (dir))) {
		RFSFile *fsf = r_fs_file_new (NULL, de->d_name);
		if (!fsf) {
			r_list_free (list);
			closedir (dir);
			return NULL;
		}
		fsf->type = 'f';
		snprintf (fullpath, sizeof (fullpath)-1, "%s/%s", path, de->d_name);
		if (!stat (fullpath, &st)) {
			fsf->type = S_ISDIR (st.st_mode)?'d':'f';
			fsf->time = st.st_atime;
		} else {
			fsf->type = 'f';
			fsf->time = 0;
		}
		r_list_append (list, fsf);
	}
	closedir (dir);
#endif
	return list;
}