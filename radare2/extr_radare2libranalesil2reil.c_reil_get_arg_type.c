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
typedef  int /*<<< orphan*/  RAnalReilArgType ;
typedef  int /*<<< orphan*/  RAnalEsil ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CONST ; 
 int /*<<< orphan*/  ARG_NONE ; 
 int /*<<< orphan*/  ARG_REG ; 
 int /*<<< orphan*/  ARG_TEMP ; 
 int /*<<< orphan*/  REIL_TEMP_PREFIX ; 
#define  R_ANAL_ESIL_PARM_NUM 129 
#define  R_ANAL_ESIL_PARM_REG 128 
 int r_anal_esil_get_parm_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RAnalReilArgType reil_get_arg_type(RAnalEsil *esil, char *s) {
	if (!strncmp (s, REIL_TEMP_PREFIX, strlen (REIL_TEMP_PREFIX))) {
		return ARG_TEMP;
	}
	int type = r_anal_esil_get_parm_type(esil, s);
	switch (type) {
	case R_ANAL_ESIL_PARM_REG:
		return ARG_REG;
	case R_ANAL_ESIL_PARM_NUM:
		return ARG_CONST;
	default:
		return ARG_NONE;
	}
}