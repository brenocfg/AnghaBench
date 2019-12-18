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
struct interface_info {TYPE_1__* client; } ;
struct client_lease {struct client_lease* next; } ;
struct TYPE_2__ {struct client_lease* active; struct client_lease* leases; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ leaseFile ; 
 int /*<<< orphan*/  path_dhclient_db ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 int /*<<< orphan*/  write_client_lease (struct interface_info*,struct client_lease*,int) ; 

void
rewrite_client_leases(struct interface_info *ifi)
{
	struct client_lease *lp;

	if (!leaseFile) {
		leaseFile = fopen(path_dhclient_db, "w");
		if (!leaseFile)
			error("can't create %s", path_dhclient_db);
	} else {
		fflush(leaseFile);
		rewind(leaseFile);
	}

	for (lp = ifi->client->leases; lp; lp = lp->next)
		write_client_lease(ifi, lp, 1);
	if (ifi->client->active)
		write_client_lease(ifi, ifi->client->active, 1);

	fflush(leaseFile);
}