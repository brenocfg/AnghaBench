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
struct afs_server_list {int nr_servers; size_t preferred; TYPE_1__* servers; } ;
struct afs_server {int dummy; } ;
struct afs_cb_interest {int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {struct afs_server* server; struct afs_cb_interest* cb_interest; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

bool afs_annotate_server_list(struct afs_server_list *new,
			      struct afs_server_list *old)
{
	struct afs_server *cur;
	int i, j;

	if (old->nr_servers != new->nr_servers)
		goto changed;

	for (i = 0; i < old->nr_servers; i++)
		if (old->servers[i].server != new->servers[i].server)
			goto changed;

	return false;

changed:
	/* Maintain the same preferred server as before if possible. */
	cur = old->servers[old->preferred].server;
	for (j = 0; j < new->nr_servers; j++) {
		if (new->servers[j].server == cur) {
			new->preferred = j;
			break;
		}
	}

	/* Keep the old callback interest records where possible so that we
	 * maintain callback interception.
	 */
	i = 0;
	j = 0;
	while (i < old->nr_servers && j < new->nr_servers) {
		if (new->servers[j].server == old->servers[i].server) {
			struct afs_cb_interest *cbi = old->servers[i].cb_interest;
			if (cbi) {
				new->servers[j].cb_interest = cbi;
				refcount_inc(&cbi->usage);
			}
			i++;
			j++;
			continue;
		}

		if (new->servers[j].server < old->servers[i].server) {
			j++;
			continue;
		}

		i++;
		continue;
	}

	return true;
}