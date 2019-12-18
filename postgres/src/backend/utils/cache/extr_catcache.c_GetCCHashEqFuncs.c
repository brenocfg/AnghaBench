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
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int Oid ;
typedef  int /*<<< orphan*/ * CCHashFN ;
typedef  int /*<<< orphan*/  CCFastEqualFN ;

/* Variables and functions */
#define  BOOLOID 145 
#define  CHAROID 144 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  F_BOOLEQ ; 
 int /*<<< orphan*/  F_CHAREQ ; 
 int /*<<< orphan*/  F_INT2EQ ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  F_OIDVECTOREQ ; 
 int /*<<< orphan*/  F_TEXTEQ ; 
#define  INT2OID 143 
#define  INT4OID 142 
 int /*<<< orphan*/  InvalidOid ; 
#define  NAMEOID 141 
#define  OIDOID 140 
#define  OIDVECTOROID 139 
#define  REGCLASSOID 138 
#define  REGCONFIGOID 137 
#define  REGDICTIONARYOID 136 
#define  REGNAMESPACEOID 135 
#define  REGOPERATOROID 134 
#define  REGOPEROID 133 
#define  REGPROCEDUREOID 132 
#define  REGPROCOID 131 
#define  REGROLEOID 130 
#define  REGTYPEOID 129 
#define  TEXTOID 128 
 int /*<<< orphan*/  chareqfast ; 
 int /*<<< orphan*/ * charhashfast ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  int2eqfast ; 
 int /*<<< orphan*/ * int2hashfast ; 
 int /*<<< orphan*/  int4eqfast ; 
 int /*<<< orphan*/ * int4hashfast ; 
 int /*<<< orphan*/  nameeqfast ; 
 int /*<<< orphan*/ * namehashfast ; 
 int /*<<< orphan*/  oidvectoreqfast ; 
 int /*<<< orphan*/ * oidvectorhashfast ; 
 int /*<<< orphan*/  texteqfast ; 
 int /*<<< orphan*/ * texthashfast ; 

__attribute__((used)) static void
GetCCHashEqFuncs(Oid keytype, CCHashFN *hashfunc, RegProcedure *eqfunc, CCFastEqualFN *fasteqfunc)
{
	switch (keytype)
	{
		case BOOLOID:
			*hashfunc = charhashfast;
			*fasteqfunc = chareqfast;
			*eqfunc = F_BOOLEQ;
			break;
		case CHAROID:
			*hashfunc = charhashfast;
			*fasteqfunc = chareqfast;
			*eqfunc = F_CHAREQ;
			break;
		case NAMEOID:
			*hashfunc = namehashfast;
			*fasteqfunc = nameeqfast;
			*eqfunc = F_NAMEEQ;
			break;
		case INT2OID:
			*hashfunc = int2hashfast;
			*fasteqfunc = int2eqfast;
			*eqfunc = F_INT2EQ;
			break;
		case INT4OID:
			*hashfunc = int4hashfast;
			*fasteqfunc = int4eqfast;
			*eqfunc = F_INT4EQ;
			break;
		case TEXTOID:
			*hashfunc = texthashfast;
			*fasteqfunc = texteqfast;
			*eqfunc = F_TEXTEQ;
			break;
		case OIDOID:
		case REGPROCOID:
		case REGPROCEDUREOID:
		case REGOPEROID:
		case REGOPERATOROID:
		case REGCLASSOID:
		case REGTYPEOID:
		case REGCONFIGOID:
		case REGDICTIONARYOID:
		case REGROLEOID:
		case REGNAMESPACEOID:
			*hashfunc = int4hashfast;
			*fasteqfunc = int4eqfast;
			*eqfunc = F_OIDEQ;
			break;
		case OIDVECTOROID:
			*hashfunc = oidvectorhashfast;
			*fasteqfunc = oidvectoreqfast;
			*eqfunc = F_OIDVECTOREQ;
			break;
		default:
			elog(FATAL, "type %u not supported as catcache key", keytype);
			*hashfunc = NULL;	/* keep compiler quiet */

			*eqfunc = InvalidOid;
			break;
	}
}