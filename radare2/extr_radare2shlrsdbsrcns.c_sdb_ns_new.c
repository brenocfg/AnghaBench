#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_11__ {TYPE_1__* name; TYPE_1__* path; } ;
struct TYPE_10__ {char const* dir; } ;
struct TYPE_9__ {struct TYPE_9__* name; TYPE_6__* sdb; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ SdbNs ;
typedef  TYPE_2__ Sdb ;

/* Variables and functions */
 int SDB_MAX_PATH ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_6__* sdb_new0 () ; 
 TYPE_1__* strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static SdbNs *sdb_ns_new (Sdb *s, const char *name, ut32 hash) {
	char dir[SDB_MAX_PATH];
	SdbNs *ns;
	if (s->dir && *s->dir && name && *name) {
		int dir_len = strlen (s->dir);
		int name_len = strlen (name);
		if ((dir_len+name_len+3)>SDB_MAX_PATH) {
			return NULL;
		}
		memcpy (dir, s->dir, dir_len);
		memcpy (dir + dir_len, ".", 1);
		memcpy (dir + dir_len + 1, name, name_len + 1);
	} else {
		dir[0] = 0;
	}
	ns = malloc (sizeof (SdbNs));
	if (!ns) {
		return NULL;
	}
	ns->hash = hash;
	ns->name = name? strdup (name): NULL;
	//ns->sdb = sdb_new (dir, ns->name, 0);
	ns->sdb = sdb_new0 ();
	// TODO: generate path

	if (ns->sdb) {
		free (ns->sdb->path);
		ns->sdb->path = NULL;
		if (*dir) {
			ns->sdb->path = strdup (dir);
		}
		free (ns->sdb->name);
		if (name && *name) {
			ns->sdb->name = strdup (name);
		}
	} else {
		free (ns->name);
		free (ns);
		ns = NULL;
	}
	return ns;
}