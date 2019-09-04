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
struct nfs_server {int dummy; } ;
struct nfs4_fs_locations {int nlocations; struct nfs4_fs_location* locations; } ;
struct TYPE_2__ {scalar_t__ ncomponents; } ;
struct nfs4_fs_location {scalar_t__ nservers; TYPE_1__ rootpath; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int nfs4_try_replacing_one_location (struct nfs_server*,char*,char*,struct nfs4_fs_location const*) ; 

int nfs4_replace_transport(struct nfs_server *server,
			   const struct nfs4_fs_locations *locations)
{
	char *page = NULL, *page2 = NULL;
	int loc, error;

	error = -ENOENT;
	if (locations == NULL || locations->nlocations <= 0)
		goto out;

	error = -ENOMEM;
	page = (char *) __get_free_page(GFP_USER);
	if (!page)
		goto out;
	page2 = (char *) __get_free_page(GFP_USER);
	if (!page2)
		goto out;

	for (loc = 0; loc < locations->nlocations; loc++) {
		const struct nfs4_fs_location *location =
						&locations->locations[loc];

		if (location == NULL || location->nservers <= 0 ||
		    location->rootpath.ncomponents == 0)
			continue;

		error = nfs4_try_replacing_one_location(server, page,
							page2, location);
		if (error == 0)
			break;
	}

out:
	free_page((unsigned long)page);
	free_page((unsigned long)page2);
	return error;
}