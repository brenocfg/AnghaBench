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

/* Variables and functions */
 char* ecpg_alloc (int,int) ; 
 int /*<<< orphan*/  ecpg_free (char*) ; 
 size_t ecpg_hex_enc_len (int) ; 
 int /*<<< orphan*/  ecpg_hex_encode (char*,int,char*) ; 
 int /*<<< orphan*/  ecpg_log (char*,int,int,char*) ; 

__attribute__((used)) static void
print_param_value(char *value, int len, int is_binary, int lineno, int nth)
{
	char	   *value_s;
	bool		malloced = false;

	if (value == NULL)
		value_s = "null";
	else if (!is_binary)
		value_s = value;
	else
	{
		value_s = ecpg_alloc(ecpg_hex_enc_len(len) + 1, lineno);
		if (value_s != NULL)
		{
			ecpg_hex_encode(value, len, value_s);
			value_s[ecpg_hex_enc_len(len)] = '\0';
			malloced = true;
		}
		else
			value_s = "no memory for logging of parameter";
	}

	ecpg_log("ecpg_free_params on line %d: parameter %d = %s\n",
			 lineno, nth, value_s);

	if (malloced)
		ecpg_free(value_s);
}