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
 int /*<<< orphan*/  E_WARNING ; 
 unsigned char* _cyr_cp866 ; 
 unsigned char* _cyr_iso88595 ; 
 unsigned char* _cyr_mac ; 
 unsigned char* _cyr_win1251 ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char) ; 
 int toupper (int) ; 

__attribute__((used)) static char * php_convert_cyr_string(unsigned char *str, size_t length, char from, char to)
{
	const unsigned char *from_table, *to_table;
	unsigned char tmp;
	size_t i;

	from_table = NULL;
	to_table   = NULL;

	switch (toupper((int)(unsigned char)from))
	{
		case 'W':
			from_table = _cyr_win1251;
			break;
		case 'A':
		case 'D':
			from_table = _cyr_cp866;
			break;
		case 'I':
			from_table = _cyr_iso88595;
			break;
		case 'M':
			from_table = _cyr_mac;
			break;
		case 'K':
			break;
		default:
			php_error_docref(NULL, E_WARNING, "Unknown source charset: %c", from);
			break;
	}

	switch (toupper((int)(unsigned char)to))
	{
		case 'W':
			to_table = _cyr_win1251;
			break;
		case 'A':
		case 'D':
			to_table = _cyr_cp866;
			break;
		case 'I':
			to_table = _cyr_iso88595;
			break;
		case 'M':
			to_table = _cyr_mac;
			break;
		case 'K':
			break;
		default:
			php_error_docref(NULL, E_WARNING, "Unknown destination charset: %c", to);
			break;
	}


	if (!str)
		return (char *)str;

	for (i = 0; i < length; i++) {
		tmp = (from_table == NULL)? str[i] : from_table[ str[i] ];
		str[i] = (to_table == NULL) ? tmp : to_table[tmp + 256];
	}
	return (char *)str;
}