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
struct dso {int /*<<< orphan*/  build_id; int /*<<< orphan*/  has_build_id; } ;

/* Variables and functions */
 int SBUILD_ID_SIZE ; 
 int asnprintf (char**,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  build_id_cache__basename (int,int,int) ; 
 char* build_id_cache__linkname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dso__is_kallsyms (struct dso*) ; 
 int dso__is_vdso (struct dso*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_regular_file (char*) ; 

char *dso__build_id_filename(const struct dso *dso, char *bf, size_t size,
			     bool is_debug)
{
	bool is_kallsyms = dso__is_kallsyms((struct dso *)dso);
	bool is_vdso = dso__is_vdso((struct dso *)dso);
	char sbuild_id[SBUILD_ID_SIZE];
	char *linkname;
	bool alloc = (bf == NULL);
	int ret;

	if (!dso->has_build_id)
		return NULL;

	build_id__sprintf(dso->build_id, sizeof(dso->build_id), sbuild_id);
	linkname = build_id_cache__linkname(sbuild_id, NULL, 0);
	if (!linkname)
		return NULL;

	/* Check if old style build_id cache */
	if (is_regular_file(linkname))
		ret = asnprintf(&bf, size, "%s", linkname);
	else
		ret = asnprintf(&bf, size, "%s/%s", linkname,
			 build_id_cache__basename(is_kallsyms, is_vdso,
						  is_debug));
	if (ret < 0 || (!alloc && size < (unsigned int)ret))
		bf = NULL;
	free(linkname);

	return bf;
}