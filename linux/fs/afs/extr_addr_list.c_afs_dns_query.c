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
typedef  scalar_t__ time64_t ;
struct afs_vlserver_list {int dummy; } ;
struct afs_cell {TYPE_1__* net; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_PORT ; 
 int ENOMEM ; 
 struct afs_vlserver_list* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct afs_vlserver_list*) ; 
 int /*<<< orphan*/  PTR_ERR (struct afs_vlserver_list*) ; 
 int /*<<< orphan*/  VL_SERVICE ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 struct afs_vlserver_list* afs_extract_vlserver_list (struct afs_cell*,char*,int) ; 
 struct afs_vlserver_list* afs_parse_text_addrs (TYPE_1__*,char*,int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dns_query (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char**,scalar_t__*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

struct afs_vlserver_list *afs_dns_query(struct afs_cell *cell, time64_t *_expiry)
{
	struct afs_vlserver_list *vllist;
	char *result = NULL;
	int ret;

	_enter("%s", cell->name);

	ret = dns_query(cell->net->net, "afsdb", cell->name, cell->name_len,
			"srv=1", &result, _expiry, true);
	if (ret < 0) {
		_leave(" = %d [dns]", ret);
		return ERR_PTR(ret);
	}

	if (*_expiry == 0)
		*_expiry = ktime_get_real_seconds() + 60;

	if (ret > 1 && result[0] == 0)
		vllist = afs_extract_vlserver_list(cell, result, ret);
	else
		vllist = afs_parse_text_addrs(cell->net, result, ret, ',',
					      VL_SERVICE, AFS_VL_PORT);
	kfree(result);
	if (IS_ERR(vllist) && vllist != ERR_PTR(-ENOMEM))
		pr_err("Failed to parse DNS data %ld\n", PTR_ERR(vllist));

	return vllist;
}