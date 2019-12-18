#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ name; } ;
struct TYPE_25__ {TYPE_2__ name; } ;
struct TYPE_19__ {scalar_t__ name; } ;
struct TYPE_24__ {TYPE_3__ name; } ;
struct TYPE_17__ {scalar_t__ name; } ;
struct TYPE_23__ {TYPE_1__ name; } ;
struct TYPE_20__ {scalar_t__ name; } ;
struct TYPE_22__ {TYPE_4__ name; } ;
struct TYPE_21__ {scalar_t__ name; } ;
struct TYPE_16__ {scalar_t__ name; } ;
struct TYPE_15__ {int value_or_type; scalar_t__ name_or_val; } ;
struct TYPE_14__ {TYPE_5__ name; } ;
typedef  TYPE_6__ SVal_LF_USHORT ;
typedef  TYPE_7__ SVal_LF_ULONG ;
typedef  TYPE_8__ SVal_LF_SHORT ;
typedef  TYPE_9__ SVal_LF_LONG ;
typedef  TYPE_10__ SVal_LF_CHAR ;
typedef  TYPE_11__ SVal ;
typedef  TYPE_12__ SCString ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (scalar_t__) ; 
#define  eLF_CHAR 132 
#define  eLF_LONG 131 
#define  eLF_SHORT 130 
#define  eLF_ULONG 129 
#define  eLF_USHORT 128 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void free_sval(SVal *val) {
	if (val->value_or_type < eLF_CHAR) {
		SCString *scstr;
		scstr = (SCString *) val->name_or_val;
		R_FREE(scstr->name);
		R_FREE(val->name_or_val);
	} else {
		switch (val->value_or_type) {
		case eLF_ULONG:
		{
			SVal_LF_ULONG *lf_ulong;
			lf_ulong = (SVal_LF_ULONG *) val->name_or_val;
			R_FREE(lf_ulong->name.name);
			R_FREE(val->name_or_val);
			break;
		}
		case eLF_LONG:
		{
			SVal_LF_LONG *lf_long;
			lf_long = (SVal_LF_LONG *) val->name_or_val;
			R_FREE(lf_long->name.name);
			R_FREE(val->name_or_val);
			break;
		}
		case eLF_SHORT:
		{
			SVal_LF_SHORT *lf_short;
			lf_short = (SVal_LF_SHORT *) val->name_or_val;
			R_FREE(lf_short->name.name);
			R_FREE(val->name_or_val);
			break;
		}
		case eLF_USHORT:
		{
			SVal_LF_USHORT *lf_ushort;
			lf_ushort = (SVal_LF_USHORT *) val->name_or_val;
			R_FREE(lf_ushort->name.name);
			R_FREE(val->name_or_val);
			break;
		}
		case eLF_CHAR:
		{
			SVal_LF_CHAR *lf_char;
			lf_char = (SVal_LF_CHAR *) val->name_or_val;
			R_FREE(lf_char->name.name);
			R_FREE(val->name_or_val);
			break;
		}
		default:
			printf("free_sval()::not supproted type\n");
			break;
		}
	}
}