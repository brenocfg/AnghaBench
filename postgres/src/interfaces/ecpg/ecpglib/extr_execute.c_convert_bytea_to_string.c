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
 int ecpg_hex_enc_len (int) ; 
 int /*<<< orphan*/  ecpg_hex_encode (char*,int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
convert_bytea_to_string(char *from_data, int from_len, int lineno)
{
	char	   *to_data;
	int			to_len = ecpg_hex_enc_len(from_len) + 4 + 1;	/* backslash + 'x' +
																 * quote + quote */

	to_data = ecpg_alloc(to_len, lineno);
	if (!to_data)
		return NULL;

	strcpy(to_data, "'\\x");
	ecpg_hex_encode(from_data, from_len, to_data + 3);
	strcpy(to_data + 3 + ecpg_hex_enc_len(from_len), "\'");

	return to_data;
}