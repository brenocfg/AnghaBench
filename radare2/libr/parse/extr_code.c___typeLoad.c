#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sdb_types; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int VT_STRUCT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* sdb_anext (char*,char**) ; 
 char* sdb_fmt (char*,char const*,...) ; 
 char* sdb_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sdb_num_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tcc_sym_push (char*,int,int) ; 

__attribute__((used)) static int __typeLoad(void *p, const char *k, const char *v) {
	if (!p) {
		return -1;
	}
	int btype = 0;
	RAnal *anal = (RAnal*)p;
	//r_cons_printf ("tk %s=%s\n", k, v);
	// TODO: Add unions support
	if (!strncmp (v, "struct", 6) && strncmp (k, "struct.", 7)) {
		// structure
		btype = VT_STRUCT;
		const char *typename = k;
		int typesize = 0;
		// TODO: Add typesize here
		char* query = sdb_fmt ("struct.%s", k);
		char *members = sdb_get (anal->sdb_types, query, 0);
		char *next, *ptr = members;
		if (members) {
			do {
				char *name = sdb_anext (ptr, &next);
				if (!name) {
					break;
				}
				query = sdb_fmt ("struct.%s.%s", k, name);
				char *subtype = sdb_get (anal->sdb_types, query, 0);
				if (!subtype) {
					break;
				}
				char *tmp = strchr (subtype, ',');
				if (tmp) {
					*tmp++ = 0;
					tmp = strchr (tmp, ',');
					if (tmp) {
						*tmp++ = 0;
					}
					char *subname = tmp;
					// TODO: Go recurse here
					query = sdb_fmt ("struct.%s.%s.meta", subtype, subname);
					btype = sdb_num_get (anal->sdb_types, query, 0);
					tcc_sym_push (subtype, 0, btype);
				}
				free (subtype);
				ptr = next;
			} while (next);
			free (members);
		}
		tcc_sym_push ((char *)typename, typesize, btype);
	}
	return 0;
}