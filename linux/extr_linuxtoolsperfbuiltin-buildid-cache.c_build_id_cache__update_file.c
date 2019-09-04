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
typedef  int /*<<< orphan*/  u8 ;
struct nsinfo {int dummy; } ;
struct nscookie {int dummy; } ;
typedef  int /*<<< orphan*/  build_id ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
 int SBUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ *,int,char*) ; 
 int build_id_cache__add_s (char*,char const*,struct nsinfo*,int,int) ; 
 scalar_t__ build_id_cache__cached (char*) ; 
 int build_id_cache__remove_s (char*) ; 
 int filename__read_build_id (char const*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (struct nsinfo*,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,...) ; 

__attribute__((used)) static int build_id_cache__update_file(const char *filename, struct nsinfo *nsi)
{
	u8 build_id[BUILD_ID_SIZE];
	char sbuild_id[SBUILD_ID_SIZE];
	struct nscookie nsc;

	int err;

	nsinfo__mountns_enter(nsi, &nsc);
	err = filename__read_build_id(filename, &build_id, sizeof(build_id));
	nsinfo__mountns_exit(&nsc);
	if (err < 0) {
		pr_debug("Couldn't read a build-id in %s\n", filename);
		return -1;
	}
	err = 0;

	build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
	if (build_id_cache__cached(sbuild_id))
		err = build_id_cache__remove_s(sbuild_id);

	if (!err)
		err = build_id_cache__add_s(sbuild_id, filename, nsi, false,
					    false);

	pr_debug("Updating %s %s: %s\n", sbuild_id, filename,
		 err ? "FAIL" : "Ok");

	return err;
}