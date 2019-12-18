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
struct ECPGgeneric_varchar {char* arr; int len; } ;
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;

/* Variables and functions */
 int /*<<< orphan*/  ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION ; 
 int /*<<< orphan*/  ECPG_VAR_NOT_CHAR ; 
#define  ECPGt_char 131 
#define  ECPGt_string 130 
#define  ECPGt_unsigned_char 129 
#define  ECPGt_varchar 128 
 int /*<<< orphan*/  ecpg_raise (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static bool
get_char_item(int lineno, void *var, enum ECPGttype vartype, char *value, int varcharsize)
{
	switch (vartype)
	{
		case ECPGt_char:
		case ECPGt_unsigned_char:
		case ECPGt_string:
			strncpy((char *) var, value, varcharsize);
			break;
		case ECPGt_varchar:
			{
				struct ECPGgeneric_varchar *variable =
				(struct ECPGgeneric_varchar *) var;

				if (varcharsize == 0)
					memcpy(variable->arr, value, strlen(value));
				else
					strncpy(variable->arr, value, varcharsize);

				variable->len = strlen(value);
				if (varcharsize > 0 && variable->len > varcharsize)
					variable->len = varcharsize;
			}
			break;
		default:
			ecpg_raise(lineno, ECPG_VAR_NOT_CHAR, ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION, NULL);
			return false;
	}

	return true;
}