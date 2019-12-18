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
typedef  int /*<<< orphan*/  R_PDB ;
typedef  int EStates ;

/* Variables and functions */
 int convert_to_state (char*) ; 
#define  eArrayState 141 
#define  eBitfieldState 140 
#define  eCharState 139 
#define  eEnumState 138 
#define  eLongState 137 
#define  eMemberState 136 
#define  eModifierState 135 
#define  eOneMethodState 134 
#define  ePointerState 133 
#define  eShortState 132 
#define  eStructState 131 
#define  eUnionState 130 
#define  eUnsignedState 129 
#define  eVoidState 128 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_name_filter (char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int build_format_flags(R_PDB *pdb, char *type, int pos, char *res_field, char **name_field) {
	EStates curr_state;
	char *tmp = 0;
	char *name = 0;

	tmp = strtok (type, " ");
	while (tmp != NULL) {
		curr_state = convert_to_state (tmp);
		switch (curr_state) {
		case eMemberState:
			break;
		case ePointerState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'p';
			break;
		case eUnionState:
		case eStructState:
			res_field[pos] = '?';
			tmp = strtok (NULL, " ");
			name = (char *) malloc (strlen (tmp) + strlen (*name_field) + 1 + 2);
			if (!name) {
				return 0;
			}
			r_name_filter (tmp, -1);
			r_name_filter (*name_field, -1);
			strcpy (name, tmp);

			sprintf (name, "(%s)%s", tmp, *name_field);
			free (*name_field);
			*name_field = name;

			return 1;
		case eUnsignedState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'u';
			break;
		case eShortState:
			// TODO: where is short??
			// where is unsigned not in hex??
			// w word (2 bytes unsigned short in hex)
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'w';
			return 1;
		case eCharState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			if (res_field[pos] == 'u') {
				res_field[pos] = 'b';
			} else {
				res_field[pos] = 'c';
			}
			return 1;
		case eLongState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'i';
			return 1;
		case eModifierState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'w';
			break;
		case eEnumState:
			if (res_field[pos] == 'p') {
				return 1;
			}
			res_field[pos] = 'E';
			tmp = strtok (NULL, " ");
			name = (char *) malloc (strlen (tmp) + strlen (*name_field) + 1 + 2);
			if (!name) {
				return 0;
			}
			strcpy (name, tmp);
			sprintf (name, "(%s)%s", tmp, *name_field);
			free (*name_field);
			*name_field = name;
			return 1;
// case eDoubleState:
//// TODO: what is the flag for double in pf??
// res_field[pos] = 'q';
// return 1;
		case eBitfieldState:
			res_field[pos] = 'B';
			tmp = strtok (NULL, " ");
			name = (char *) malloc (strlen (tmp) + strlen (*name_field) + 1 + 2);
			if (!name) {
				return 0;
			}
			strcpy (name, tmp);
			sprintf (name, "(%s)%s", tmp, *name_field);
			free (*name_field);
			*name_field = name;
			return 1;
		case eVoidState:
		case eArrayState:
		case eOneMethodState:
			res_field[pos] = 'p';
			return 1;
		default:
			if (((!strcmp (tmp, "to"))) ||
			    (!strcmp (tmp, "nesttype")) ||
			    (!strcmp (tmp, "mfunction")) ||
			    (!strcmp (tmp, "proc")) ||
			    (!strcmp (tmp, "arglist"))) {
				break;
			} else {
				//eprintf ("There is no support for type \"%s\" in PF structs\n", tmp);
				res_field[pos] = 'A';
				return 0;
			}
		}

		tmp = strtok (NULL, " ");
	}

	return 1;
}