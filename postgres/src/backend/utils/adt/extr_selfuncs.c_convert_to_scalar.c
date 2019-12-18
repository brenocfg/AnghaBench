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
typedef  int Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
#define  BOOLOID 161 
#define  BPCHAROID 160 
#define  BYTEAOID 159 
#define  CHAROID 158 
#define  CIDROID 157 
#define  DATEOID 156 
#define  FLOAT4OID 155 
#define  FLOAT8OID 154 
#define  INETOID 153 
#define  INT2OID 152 
#define  INT4OID 151 
#define  INT8OID 150 
#define  INTERVALOID 149 
#define  MACADDR8OID 148 
#define  MACADDROID 147 
#define  NAMEOID 146 
#define  NUMERICOID 145 
#define  OIDOID 144 
#define  REGCLASSOID 143 
#define  REGCONFIGOID 142 
#define  REGDICTIONARYOID 141 
#define  REGNAMESPACEOID 140 
#define  REGOPERATOROID 139 
#define  REGOPEROID 138 
#define  REGPROCEDUREOID 137 
#define  REGPROCOID 136 
#define  REGROLEOID 135 
#define  REGTYPEOID 134 
#define  TEXTOID 133 
#define  TIMEOID 132 
#define  TIMESTAMPOID 131 
#define  TIMESTAMPTZOID 130 
#define  TIMETZOID 129 
#define  VARCHAROID 128 
 int /*<<< orphan*/  convert_bytea_to_scalar (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,double*) ; 
 double convert_network_to_scalar (int /*<<< orphan*/ ,int,int*) ; 
 double convert_numeric_to_scalar (int /*<<< orphan*/ ,int,int*) ; 
 char* convert_string_datum (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  convert_string_to_scalar (char*,double*,char*,double*,char*,double*) ; 
 double convert_timevalue_to_scalar (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static bool
convert_to_scalar(Datum value, Oid valuetypid, Oid collid, double *scaledvalue,
				  Datum lobound, Datum hibound, Oid boundstypid,
				  double *scaledlobound, double *scaledhibound)
{
	bool		failure = false;

	/*
	 * Both the valuetypid and the boundstypid should exactly match the
	 * declared input type(s) of the operator we are invoked for.  However,
	 * extensions might try to use scalarineqsel as estimator for operators
	 * with input type(s) we don't handle here; in such cases, we want to
	 * return false, not fail.  In any case, we mustn't assume that valuetypid
	 * and boundstypid are identical.
	 *
	 * XXX The histogram we are interpolating between points of could belong
	 * to a column that's only binary-compatible with the declared type. In
	 * essence we are assuming that the semantics of binary-compatible types
	 * are enough alike that we can use a histogram generated with one type's
	 * operators to estimate selectivity for the other's.  This is outright
	 * wrong in some cases --- in particular signed versus unsigned
	 * interpretation could trip us up.  But it's useful enough in the
	 * majority of cases that we do it anyway.  Should think about more
	 * rigorous ways to do it.
	 */
	switch (valuetypid)
	{
			/*
			 * Built-in numeric types
			 */
		case BOOLOID:
		case INT2OID:
		case INT4OID:
		case INT8OID:
		case FLOAT4OID:
		case FLOAT8OID:
		case NUMERICOID:
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
			*scaledvalue = convert_numeric_to_scalar(value, valuetypid,
													 &failure);
			*scaledlobound = convert_numeric_to_scalar(lobound, boundstypid,
													   &failure);
			*scaledhibound = convert_numeric_to_scalar(hibound, boundstypid,
													   &failure);
			return !failure;

			/*
			 * Built-in string types
			 */
		case CHAROID:
		case BPCHAROID:
		case VARCHAROID:
		case TEXTOID:
		case NAMEOID:
			{
				char	   *valstr = convert_string_datum(value, valuetypid,
														  collid, &failure);
				char	   *lostr = convert_string_datum(lobound, boundstypid,
														 collid, &failure);
				char	   *histr = convert_string_datum(hibound, boundstypid,
														 collid, &failure);

				/*
				 * Bail out if any of the values is not of string type.  We
				 * might leak converted strings for the other value(s), but
				 * that's not worth troubling over.
				 */
				if (failure)
					return false;

				convert_string_to_scalar(valstr, scaledvalue,
										 lostr, scaledlobound,
										 histr, scaledhibound);
				pfree(valstr);
				pfree(lostr);
				pfree(histr);
				return true;
			}

			/*
			 * Built-in bytea type
			 */
		case BYTEAOID:
			{
				/* We only support bytea vs bytea comparison */
				if (boundstypid != BYTEAOID)
					return false;
				convert_bytea_to_scalar(value, scaledvalue,
										lobound, scaledlobound,
										hibound, scaledhibound);
				return true;
			}

			/*
			 * Built-in time types
			 */
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
		case DATEOID:
		case INTERVALOID:
		case TIMEOID:
		case TIMETZOID:
			*scaledvalue = convert_timevalue_to_scalar(value, valuetypid,
													   &failure);
			*scaledlobound = convert_timevalue_to_scalar(lobound, boundstypid,
														 &failure);
			*scaledhibound = convert_timevalue_to_scalar(hibound, boundstypid,
														 &failure);
			return !failure;

			/*
			 * Built-in network types
			 */
		case INETOID:
		case CIDROID:
		case MACADDROID:
		case MACADDR8OID:
			*scaledvalue = convert_network_to_scalar(value, valuetypid,
													 &failure);
			*scaledlobound = convert_network_to_scalar(lobound, boundstypid,
													   &failure);
			*scaledhibound = convert_network_to_scalar(hibound, boundstypid,
													   &failure);
			return !failure;
	}
	/* Don't know how to convert */
	*scaledvalue = *scaledlobound = *scaledhibound = 0;
	return false;
}