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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ FirstBootstrapObjectId ; 

bool
IsCatalogRelationOid(Oid relid)
{
	/*
	 * We consider a relation to be a system catalog if it has an OID that was
	 * manually assigned or assigned by genbki.pl.  This includes all the
	 * defined catalogs, their indexes, and their TOAST tables and indexes.
	 *
	 * This rule excludes the relations in information_schema, which are not
	 * integral to the system and can be treated the same as user relations.
	 * (Since it's valid to drop and recreate information_schema, any rule
	 * that did not act this way would be wrong.)
	 *
	 * This test is reliable since an OID wraparound will skip this range of
	 * OIDs; see GetNewObjectId().
	 */
	return (relid < (Oid) FirstBootstrapObjectId);
}