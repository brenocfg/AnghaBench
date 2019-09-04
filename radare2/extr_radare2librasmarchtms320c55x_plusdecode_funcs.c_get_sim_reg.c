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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 char* get_reg_name_1 (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strcat_dup (char*,char*,int) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 char* strdup (char*) ; 

char *get_sim_reg (char *reg_arg, ut32 ins_bits) {
	st32 code;
	char *res = NULL;
	char *aux;
	code = ins_bits & 3;
	switch (code) {
	case 0:
		if(reg_arg && strchr (reg_arg, 'w')) {
			if(code == 62) {
				return strdup ("sim0");
			}
			if(code == 63) {
				return strdup ("sim0");
			}
		}
		aux = get_reg_name_1 (ins_bits >> 2);
		res = strcat_dup ("@", aux, 2);
		break;
	case 2:
		aux = (char *)calloc (1, 50);
		if (!aux) {
			return NULL;
		}
		sprintf (aux, "@#0x%x", code);
		res = aux;
		break;
	case 1:
	case 3:
		res = strdup ("<reserved>");
		break;
	}
	return res;
}