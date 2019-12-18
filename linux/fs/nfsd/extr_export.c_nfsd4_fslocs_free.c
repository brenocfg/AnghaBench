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
struct nfsd4_fs_locations {int locations_count; struct nfsd4_fs_location* locations; } ;
struct nfsd4_fs_location {struct nfsd4_fs_location* hosts; struct nfsd4_fs_location* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfsd4_fs_location*) ; 

__attribute__((used)) static void nfsd4_fslocs_free(struct nfsd4_fs_locations *fsloc)
{
	struct nfsd4_fs_location *locations = fsloc->locations;
	int i;

	if (!locations)
		return;

	for (i = 0; i < fsloc->locations_count; i++) {
		kfree(locations[i].path);
		kfree(locations[i].hosts);
	}

	kfree(locations);
	fsloc->locations = NULL;
}