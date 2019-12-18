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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  NamespaceInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * findNamespaceByOid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static NamespaceInfo *
findNamespace(Archive *fout, Oid nsoid)
{
	NamespaceInfo *nsinfo;

	nsinfo = findNamespaceByOid(nsoid);
	if (nsinfo == NULL)
		fatal("schema with OID %u does not exist", nsoid);
	return nsinfo;
}