#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  short zend_long ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_6__ {int dsc_flags; int dsc_dtype; int dsc_length; size_t dsc_scale; scalar_t__ dsc_address; } ;
struct TYPE_5__ {char* vary_string; int vary_length; } ;
typedef  TYPE_1__ PARAMVARY ;
typedef  TYPE_2__ PARAMDSC ;
typedef  int /*<<< orphan*/  ISC_TIMESTAMP ;
typedef  int /*<<< orphan*/  ISC_TIME ;
typedef  short ISC_LONG ;
typedef  scalar_t__ ISC_INT64 ;
typedef  int /*<<< orphan*/  ISC_DATE ;

/* Variables and functions */
 int DSC_null ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  INI_STR (char*) ; 
#define  IS_DOUBLE 142 
#define  IS_LONG 141 
#define  IS_NULL 140 
#define  IS_STRING 139 
 int /*<<< orphan*/  LOCK () ; 
 int /*<<< orphan*/  UNLOCK () ; 
 scalar_t__ ZEND_LONG_MAX ; 
 scalar_t__ ZEND_LONG_MIN ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,short) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int,...) ; 
 double Z_DVAL (int /*<<< orphan*/ ) ; 
 short Z_LVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ *) ; 
#define  dtype_cstring 138 
#define  dtype_double 137 
#define  dtype_int64 136 
#define  dtype_long 135 
#define  dtype_real 134 
#define  dtype_short 133 
#define  dtype_sql_date 132 
#define  dtype_sql_time 131 
#define  dtype_text 130 
#define  dtype_timestamp 129 
#define  dtype_varying 128 
 int /*<<< orphan*/  isc_decode_sql_date (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  isc_decode_sql_time (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  isc_decode_timestamp (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 double* scales ; 
 int strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  zend_is_callable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_php(char *name, PARAMDSC *r, int argc, PARAMDSC **argv)
{
	do {
		zval callback, args[4], return_value;
		PARAMVARY *res = (PARAMVARY*)r->dsc_address;
		int i;

		ZVAL_STRING(&callback, name);

		LOCK();

		/* check if the requested function exists */
		if (!zend_is_callable(&callback, 0, NULL)) {
			break;
		}

		UNLOCK();

		/* create the argument array */
		for (i = 0; i < argc; ++i) {

			/* test arg for null */
			if (argv[i]->dsc_flags & DSC_null) {
				ZVAL_NULL(&args[i]);
				continue;
			}

			switch (argv[i]->dsc_dtype) {
				ISC_INT64 l;
				struct tm t;
				char const *fmt;
				char d[64];

				case dtype_cstring:
//???
					ZVAL_STRING(&args[i], (char*)argv[i]->dsc_address);
					break;

				case dtype_text:
//???
					ZVAL_STRINGL(&args[i], (char*)argv[i]->dsc_address, argv[i]->dsc_length);
					break;

				case dtype_varying:
//???
					ZVAL_STRINGL(&args[i], ((PARAMVARY*)argv[i]->dsc_address)->vary_string,
						((PARAMVARY*)argv[i]->dsc_address)->vary_length);
					break;

				case dtype_short:
					if (argv[i]->dsc_scale == 0) {
						ZVAL_LONG(&args[i], *(short*)argv[i]->dsc_address);
					} else {
						ZVAL_DOUBLE(&args[i],
							((double)*(short*)argv[i]->dsc_address)/scales[-argv[i]->dsc_scale]);
					}
					break;

				case dtype_long:
					if (argv[i]->dsc_scale == 0) {
						ZVAL_LONG(&args[i], *(ISC_LONG*)argv[i]->dsc_address);
					} else {
						ZVAL_DOUBLE(&args[i],
							((double)*(ISC_LONG*)argv[i]->dsc_address)/scales[-argv[i]->dsc_scale]);
					}
					break;

				case dtype_int64:
					l = *(ISC_INT64*)argv[i]->dsc_address;

					if (argv[i]->dsc_scale == 0 && l <= ZEND_LONG_MAX && l >= ZEND_LONG_MIN) {
						ZVAL_LONG(&args[i], (zend_long)l);
					} else {
						ZVAL_DOUBLE(&args[i], ((double)l)/scales[-argv[i]->dsc_scale]);
					}
					break;

				case dtype_real:
					ZVAL_DOUBLE(&args[i], *(float*)argv[i]->dsc_address);
					break;

				case dtype_double:
					ZVAL_DOUBLE(&args[i], *(double*)argv[i]->dsc_address);
					break;

				case dtype_sql_date:
					isc_decode_sql_date((ISC_DATE*)argv[i]->dsc_address, &t);
					ZVAL_STRINGL(&args[i], d, strftime(d, sizeof(d), INI_STR("ibase.dateformat"), &t),1);
					break;

				case dtype_sql_time:
					isc_decode_sql_time((ISC_TIME*)argv[i]->dsc_address, &t);
					ZVAL_STRINGL(&args[i], d, strftime(d, sizeof(d), INI_STR("ibase.timeformat"), &t),1);
					break;

				case dtype_timestamp:
					isc_decode_timestamp((ISC_TIMESTAMP*)argv[i]->dsc_address, &t);
					ZVAL_STRINGL(&args[i], d, strftime(d, sizeof(d), INI_STR("ibase.timestampformat"), &t));
					break;
			}
		}

		LOCK();

		/* now call the function */
		if (FAILURE == call_user_function(NULL, NULL,
				&callback, &return_value, argc, args)) {
			UNLOCK();
			break;
		}

		UNLOCK();

		for (i = 0; i < argc; ++i) {
			switch (argv[i]->dsc_dtype) {
				case dtype_sql_date:
				case dtype_sql_time:
				case dtype_timestamp:
					zval_ptr_dtor_nogc(&args[i]);
			}
		}

		zval_ptr_dtor_str(&callback);

		/* return whatever type we got back from the callback: let DB handle conversion */
		switch (Z_TYPE(return_value)) {

			case IS_LONG:
				r->dsc_dtype = dtype_long;
				*(zend_long*)r->dsc_address = Z_LVAL(return_value);
				r->dsc_length = sizeof(zend_long);
				break;

			case IS_DOUBLE:
				r->dsc_dtype = dtype_double;
				*(double*)r->dsc_address = Z_DVAL(return_value);
				r->dsc_length = sizeof(double);
				break;

			case IS_NULL:
				r->dsc_flags |= DSC_null;
				break;

			default:
				convert_to_string(&return_value);

			case IS_STRING:
				r->dsc_dtype = dtype_varying;
				memcpy(res->vary_string, Z_STRVAL(return_value),
					(res->vary_length = min(r->dsc_length-2,Z_STRLEN(return_value))));
				r->dsc_length = res->vary_length+2;
				break;
		}

		zval_ptr_dtor(&return_value);

		return;

	} while (0);

	/**
	* If we end up here, we should report an error back to the DB engine, but
	* that's not possible. We can however report it back to PHP.
	*/
	LOCK();
	php_error_docref(NULL, E_WARNING, "Error calling function '%s' from database", name);
	UNLOCK();
}