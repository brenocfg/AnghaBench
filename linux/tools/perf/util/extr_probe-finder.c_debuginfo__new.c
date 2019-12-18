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
struct dso {int dummy; } ;
struct debuginfo {int dummy; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;

/* Variables and functions */
 int DSO_BINARY_TYPE__NOT_FOUND ; 
 int PATH_MAX ; 
 struct debuginfo* __debuginfo__new (char const*) ; 
 int* distro_dwarf_types ; 
 struct dso* dso__new (char const*) ; 
 int /*<<< orphan*/  dso__put (struct dso*) ; 
 scalar_t__ dso__read_binary_type_filename (struct dso*,int,char*,char*,int) ; 

struct debuginfo *debuginfo__new(const char *path)
{
	enum dso_binary_type *type;
	char buf[PATH_MAX], nil = '\0';
	struct dso *dso;
	struct debuginfo *dinfo = NULL;

	/* Try to open distro debuginfo files */
	dso = dso__new(path);
	if (!dso)
		goto out;

	for (type = distro_dwarf_types;
	     !dinfo && *type != DSO_BINARY_TYPE__NOT_FOUND;
	     type++) {
		if (dso__read_binary_type_filename(dso, *type, &nil,
						   buf, PATH_MAX) < 0)
			continue;
		dinfo = __debuginfo__new(buf);
	}
	dso__put(dso);

out:
	/* if failed to open all distro debuginfo, open given binary */
	return dinfo ? : __debuginfo__new(path);
}