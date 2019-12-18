#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timestamp ;
struct ECPGgeneric_varchar {int* arr; int /*<<< orphan*/  len; } ;
struct ECPGgeneric_bytea {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {void* sign; } ;
typedef  TYPE_1__ numeric ;
typedef  int /*<<< orphan*/  interval ;
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;
struct TYPE_4__ {void* sign; } ;
typedef  TYPE_2__ decimal ;

/* Variables and functions */
#define  ECPGt_bytea 147 
#define  ECPGt_char 146 
#define  ECPGt_date 145 
#define  ECPGt_decimal 144 
#define  ECPGt_double 143 
#define  ECPGt_float 142 
#define  ECPGt_int 141 
#define  ECPGt_interval 140 
#define  ECPGt_long 139 
#define  ECPGt_long_long 138 
#define  ECPGt_numeric 137 
#define  ECPGt_short 136 
#define  ECPGt_string 135 
#define  ECPGt_timestamp 134 
#define  ECPGt_unsigned_char 133 
#define  ECPGt_unsigned_int 132 
#define  ECPGt_unsigned_long 131 
#define  ECPGt_unsigned_long_long 130 
#define  ECPGt_unsigned_short 129 
#define  ECPGt_varchar 128 
 int INT_MIN ; 
 long long LONG_LONG_MIN ; 
 long LONG_MIN ; 
 void* NUMERIC_NULL ; 
 short SHRT_MIN ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

void
ECPGset_noind_null(enum ECPGttype type, void *ptr)
{
	switch (type)
	{
		case ECPGt_char:
		case ECPGt_unsigned_char:
		case ECPGt_string:
			*((char *) ptr) = '\0';
			break;
		case ECPGt_short:
		case ECPGt_unsigned_short:
			*((short int *) ptr) = SHRT_MIN;
			break;
		case ECPGt_int:
		case ECPGt_unsigned_int:
			*((int *) ptr) = INT_MIN;
			break;
		case ECPGt_long:
		case ECPGt_unsigned_long:
		case ECPGt_date:
			*((long *) ptr) = LONG_MIN;
			break;
		case ECPGt_long_long:
		case ECPGt_unsigned_long_long:
			*((long long *) ptr) = LONG_LONG_MIN;
			break;
		case ECPGt_float:
			memset((char *) ptr, 0xff, sizeof(float));
			break;
		case ECPGt_double:
			memset((char *) ptr, 0xff, sizeof(double));
			break;
		case ECPGt_varchar:
			*(((struct ECPGgeneric_varchar *) ptr)->arr) = 0x00;
			((struct ECPGgeneric_varchar *) ptr)->len = 0;
			break;
		case ECPGt_bytea:
			((struct ECPGgeneric_bytea *) ptr)->len = 0;
			break;
		case ECPGt_decimal:
			memset((char *) ptr, 0, sizeof(decimal));
			((decimal *) ptr)->sign = NUMERIC_NULL;
			break;
		case ECPGt_numeric:
			memset((char *) ptr, 0, sizeof(numeric));
			((numeric *) ptr)->sign = NUMERIC_NULL;
			break;
		case ECPGt_interval:
			memset((char *) ptr, 0xff, sizeof(interval));
			break;
		case ECPGt_timestamp:
			memset((char *) ptr, 0xff, sizeof(timestamp));
			break;
		default:
			break;
	}
}