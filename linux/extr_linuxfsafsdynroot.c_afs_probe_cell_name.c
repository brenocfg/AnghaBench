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
struct TYPE_2__ {char* name; size_t len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  IS_ERR (struct afs_cell*) ; 
 int /*<<< orphan*/  afs_d2net (struct dentry*) ; 
 struct afs_cell* afs_lookup_cell_rcu (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  afs_put_cell (int /*<<< orphan*/ ,struct afs_cell*) ; 
 int dns_query (char*,char const*,size_t,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_probe_cell_name(struct dentry *dentry)
{
	struct afs_cell *cell;
	const char *name = dentry->d_name.name;
	size_t len = dentry->d_name.len;
	int ret;

	/* Names prefixed with a dot are R/W mounts. */
	if (name[0] == '.') {
		if (len == 1)
			return -EINVAL;
		name++;
		len--;
	}

	cell = afs_lookup_cell_rcu(afs_d2net(dentry), name, len);
	if (!IS_ERR(cell)) {
		afs_put_cell(afs_d2net(dentry), cell);
		return 0;
	}

	ret = dns_query("afsdb", name, len, "", NULL, NULL);
	if (ret == -ENODATA)
		ret = -EDESTADDRREQ;
	return ret;
}