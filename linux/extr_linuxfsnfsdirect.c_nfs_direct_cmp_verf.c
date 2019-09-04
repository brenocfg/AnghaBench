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
struct nfs_writeverf {int /*<<< orphan*/  verifier; } ;

/* Variables and functions */
 int nfs_write_verifier_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_direct_cmp_verf(const struct nfs_writeverf *v1,
		const struct nfs_writeverf *v2)
{
	return nfs_write_verifier_cmp(&v1->verifier, &v2->verifier);
}