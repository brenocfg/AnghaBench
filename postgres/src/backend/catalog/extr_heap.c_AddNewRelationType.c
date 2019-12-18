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
typedef  int /*<<< orphan*/  ObjectAddress ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TYPDELIM ; 
 int /*<<< orphan*/  F_RECORD_IN ; 
 int /*<<< orphan*/  F_RECORD_OUT ; 
 int /*<<< orphan*/  F_RECORD_RECV ; 
 int /*<<< orphan*/  F_RECORD_SEND ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  TYPCATEGORY_COMPOSITE ; 
 int /*<<< orphan*/  TYPTYPE_COMPOSITE ; 
 int /*<<< orphan*/  TypeCreate (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char,char,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
AddNewRelationType(const char *typeName,
				   Oid typeNamespace,
				   Oid new_rel_oid,
				   char new_rel_kind,
				   Oid ownerid,
				   Oid new_row_type,
				   Oid new_array_type)
{
	return
		TypeCreate(new_row_type,	/* optional predetermined OID */
				   typeName,	/* type name */
				   typeNamespace,	/* type namespace */
				   new_rel_oid, /* relation oid */
				   new_rel_kind,	/* relation kind */
				   ownerid,		/* owner's ID */
				   -1,			/* internal size (varlena) */
				   TYPTYPE_COMPOSITE,	/* type-type (composite) */
				   TYPCATEGORY_COMPOSITE,	/* type-category (ditto) */
				   false,		/* composite types are never preferred */
				   DEFAULT_TYPDELIM,	/* default array delimiter */
				   F_RECORD_IN, /* input procedure */
				   F_RECORD_OUT,	/* output procedure */
				   F_RECORD_RECV,	/* receive procedure */
				   F_RECORD_SEND,	/* send procedure */
				   InvalidOid,	/* typmodin procedure - none */
				   InvalidOid,	/* typmodout procedure - none */
				   InvalidOid,	/* analyze procedure - default */
				   InvalidOid,	/* array element type - irrelevant */
				   false,		/* this is not an array type */
				   new_array_type,	/* array type if any */
				   InvalidOid,	/* domain base type - irrelevant */
				   NULL,		/* default value - none */
				   NULL,		/* default binary representation */
				   false,		/* passed by reference */
				   'd',			/* alignment - must be the largest! */
				   'x',			/* fully TOASTable */
				   -1,			/* typmod */
				   0,			/* array dimensions for typBaseType */
				   false,		/* Type NOT NULL */
				   InvalidOid); /* rowtypes never have a collation */
}