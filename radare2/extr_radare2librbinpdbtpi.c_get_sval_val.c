#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int value_or_type; scalar_t__ name_or_val; } ;
struct TYPE_16__ {int value; } ;
struct TYPE_15__ {int value; } ;
struct TYPE_14__ {int value; } ;
struct TYPE_13__ {int value; } ;
struct TYPE_12__ {int value; } ;
struct TYPE_11__ {int value; } ;
struct TYPE_10__ {int value; } ;
typedef  TYPE_1__ SVal_LF_USHORT ;
typedef  TYPE_2__ SVal_LF_UQUADWORD ;
typedef  TYPE_3__ SVal_LF_ULONG ;
typedef  TYPE_4__ SVal_LF_SHORT ;
typedef  TYPE_5__ SVal_LF_QUADWORD ;
typedef  TYPE_6__ SVal_LF_LONG ;
typedef  TYPE_7__ SVal_LF_CHAR ;
typedef  TYPE_8__ SVal ;

/* Variables and functions */
#define  eLF_CHAR 134 
#define  eLF_LONG 133 
#define  eLF_QUADWORD 132 
#define  eLF_SHORT 131 
#define  eLF_ULONG 130 
#define  eLF_UQUADWORD 129 
#define  eLF_USHORT 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void get_sval_val(SVal *val, int *res) {
	if (val->value_or_type < eLF_CHAR) {
		*res = val->value_or_type;
	} else {
		switch (val->value_or_type) {
		case eLF_UQUADWORD:
		{
			SVal_LF_UQUADWORD *lf_uqword;
			lf_uqword = (SVal_LF_UQUADWORD *) val->name_or_val;
			*res = lf_uqword->value;
			break;
		}
		case eLF_QUADWORD:
		{
			SVal_LF_QUADWORD *lf_qword;
			lf_qword = (SVal_LF_QUADWORD *) val->name_or_val;
			*res = lf_qword->value;
			break;
		}
		case eLF_ULONG:
		{
			SVal_LF_ULONG *lf_ulong;
			lf_ulong = (SVal_LF_ULONG *) val->name_or_val;
			*res = lf_ulong->value;
			break;
		}
		case eLF_LONG:
		{
			SVal_LF_LONG *lf_long;
			lf_long = (SVal_LF_LONG *) val->name_or_val;
			*res = lf_long->value;
			break;
		}
		case eLF_USHORT:
		{
			SVal_LF_USHORT *lf_ushort;
			lf_ushort = (SVal_LF_USHORT *) val->name_or_val;
			*res = lf_ushort->value;
			break;
		}
		case eLF_SHORT:
		{
			SVal_LF_SHORT *lf_short;
			lf_short = (SVal_LF_SHORT *) val->name_or_val;
			*res = lf_short->value;
			break;
		}
		case eLF_CHAR:
		{
			SVal_LF_CHAR *lf_char;
			lf_char = (SVal_LF_CHAR *) val->name_or_val;
			*res = lf_char->value;
			break;
		}

		default:
			*res = 0;
			printf("get_sval_val: Skipping unsupported type (%d)\n", val->value_or_type);
			break;
		}
	}
}