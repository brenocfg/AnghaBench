#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int size; } ;
struct TYPE_12__ {int value_or_type; scalar_t__ name_or_val; } ;
struct TYPE_8__ {int size; } ;
struct TYPE_11__ {TYPE_1__ name; } ;
struct TYPE_9__ {int size; } ;
struct TYPE_10__ {TYPE_2__ name; } ;
typedef  TYPE_3__ SVal_LF_USHORT ;
typedef  TYPE_4__ SVal_LF_ULONG ;
typedef  TYPE_5__ SVal ;
typedef  TYPE_6__ SCString ;

/* Variables and functions */
 int eLF_CHAR ; 
#define  eLF_ULONG 129 
#define  eLF_USHORT 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void get_sval_name_len(SVal *val, int *res_len) {
	if (val->value_or_type < eLF_CHAR) {
		SCString *scstr = (SCString *) val->name_or_val;
		*res_len = scstr->size;
	} else {
		switch (val->value_or_type) {
		case eLF_ULONG:
		{
			SVal_LF_ULONG *lf_ulong;
			lf_ulong = (SVal_LF_ULONG *) val->name_or_val;
			*res_len = lf_ulong->name.size;
			break;
		}
		case eLF_USHORT:
		{
			SVal_LF_USHORT *lf_ushort;
			lf_ushort = (SVal_LF_USHORT *) val->name_or_val;
			*res_len = lf_ushort->name.size;
			break;
		}
		default:
			*res_len = 0;
			printf("get_sval_name_len: Skipping unsupported type (%d)\n", val->value_or_type);
			break;
		}
	}
}