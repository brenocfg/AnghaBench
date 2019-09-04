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
typedef  int /*<<< orphan*/  time64_t ;
struct afs_cell {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct afs_addr_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_PORT ; 
 int ENOMEM ; 
 struct afs_addr_list* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct afs_addr_list*) ; 
 int /*<<< orphan*/  VL_SERVICE ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 struct afs_addr_list* afs_parse_text_addrs (char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dns_query (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

struct afs_addr_list *afs_dns_query(struct afs_cell *cell, time64_t *_expiry)
{
	struct afs_addr_list *alist;
	char *vllist = NULL;
	int ret;

	_enter("%s", cell->name);

	ret = dns_query("afsdb", cell->name, cell->name_len,
			"", &vllist, _expiry);
	if (ret < 0)
		return ERR_PTR(ret);

	alist = afs_parse_text_addrs(vllist, strlen(vllist), ',',
				     VL_SERVICE, AFS_VL_PORT);
	if (IS_ERR(alist)) {
		kfree(vllist);
		if (alist != ERR_PTR(-ENOMEM))
			pr_err("Failed to parse DNS data\n");
		return alist;
	}

	kfree(vllist);
	return alist;
}