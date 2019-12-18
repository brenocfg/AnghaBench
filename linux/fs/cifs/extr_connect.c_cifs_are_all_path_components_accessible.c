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
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct TCP_Server_Info {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* is_path_accessible ) (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ;} ;

/* Variables and functions */
 char CIFS_DIR_SEP (struct cifs_sb_info*) ; 
 int stub1 (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ; 
 int stub2 (unsigned int,struct cifs_tcon*,struct cifs_sb_info*,char*) ; 

__attribute__((used)) static int
cifs_are_all_path_components_accessible(struct TCP_Server_Info *server,
					unsigned int xid,
					struct cifs_tcon *tcon,
					struct cifs_sb_info *cifs_sb,
					char *full_path,
					int added_treename)
{
	int rc;
	char *s;
	char sep, tmp;
	int skip = added_treename ? 1 : 0;

	sep = CIFS_DIR_SEP(cifs_sb);
	s = full_path;

	rc = server->ops->is_path_accessible(xid, tcon, cifs_sb, "");
	while (rc == 0) {
		/* skip separators */
		while (*s == sep)
			s++;
		if (!*s)
			break;
		/* next separator */
		while (*s && *s != sep)
			s++;
		/*
		 * if the treename is added, we then have to skip the first
		 * part within the separators
		 */
		if (skip) {
			skip = 0;
			continue;
		}
		/*
		 * temporarily null-terminate the path at the end of
		 * the current component
		 */
		tmp = *s;
		*s = 0;
		rc = server->ops->is_path_accessible(xid, tcon, cifs_sb,
						     full_path);
		*s = tmp;
	}
	return rc;
}