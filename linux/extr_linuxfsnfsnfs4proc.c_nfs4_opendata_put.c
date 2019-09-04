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
struct nfs4_opendata {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_opendata_free ; 

__attribute__((used)) static void nfs4_opendata_put(struct nfs4_opendata *p)
{
	if (p != NULL)
		kref_put(&p->kref, nfs4_opendata_free);
}