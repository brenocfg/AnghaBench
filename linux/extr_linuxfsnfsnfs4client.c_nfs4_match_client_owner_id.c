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
struct nfs_client {int /*<<< orphan*/ * cl_owner_id; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nfs4_match_client_owner_id(const struct nfs_client *clp1,
		const struct nfs_client *clp2)
{
	if (clp1->cl_owner_id == NULL || clp2->cl_owner_id == NULL)
		return true;
	return strcmp(clp1->cl_owner_id, clp2->cl_owner_id) == 0;
}