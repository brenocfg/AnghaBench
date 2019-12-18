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

/* Variables and functions */
#define  F_RI_FKEY_CASCADE_DEL 139 
#define  F_RI_FKEY_CASCADE_UPD 138 
#define  F_RI_FKEY_CHECK_INS 137 
#define  F_RI_FKEY_CHECK_UPD 136 
#define  F_RI_FKEY_NOACTION_DEL 135 
#define  F_RI_FKEY_NOACTION_UPD 134 
#define  F_RI_FKEY_RESTRICT_DEL 133 
#define  F_RI_FKEY_RESTRICT_UPD 132 
#define  F_RI_FKEY_SETDEFAULT_DEL 131 
#define  F_RI_FKEY_SETDEFAULT_UPD 130 
#define  F_RI_FKEY_SETNULL_DEL 129 
#define  F_RI_FKEY_SETNULL_UPD 128 
 int RI_TRIGGER_FK ; 
 int RI_TRIGGER_NONE ; 
 int RI_TRIGGER_PK ; 

int
RI_FKey_trigger_type(Oid tgfoid)
{
	switch (tgfoid)
	{
		case F_RI_FKEY_CASCADE_DEL:
		case F_RI_FKEY_CASCADE_UPD:
		case F_RI_FKEY_RESTRICT_DEL:
		case F_RI_FKEY_RESTRICT_UPD:
		case F_RI_FKEY_SETNULL_DEL:
		case F_RI_FKEY_SETNULL_UPD:
		case F_RI_FKEY_SETDEFAULT_DEL:
		case F_RI_FKEY_SETDEFAULT_UPD:
		case F_RI_FKEY_NOACTION_DEL:
		case F_RI_FKEY_NOACTION_UPD:
			return RI_TRIGGER_PK;

		case F_RI_FKEY_CHECK_INS:
		case F_RI_FKEY_CHECK_UPD:
			return RI_TRIGGER_FK;
	}

	return RI_TRIGGER_NONE;
}