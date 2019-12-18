#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct os_globent {int path; int /*<<< orphan*/  directory; } ;
struct dstr {int array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_from_wcs (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_resize (struct dstr*,char*) ; 
 int /*<<< orphan*/  is_dir (TYPE_1__*) ; 
 char* strrchr (int,char) ; 

__attribute__((used)) static void make_globent(struct os_globent *ent, WIN32_FIND_DATA *wfd,
			 const char *pattern)
{
	struct dstr name = {0};
	struct dstr path = {0};
	char *slash;

	dstr_from_wcs(&name, wfd->cFileName);
	dstr_copy(&path, pattern);
	slash = strrchr(path.array, '/');
	if (slash)
		dstr_resize(&path, slash + 1 - path.array);
	else
		dstr_free(&path);

	dstr_cat_dstr(&path, &name);
	ent->path = path.array;
	ent->directory = is_dir(wfd);

	dstr_free(&name);
}