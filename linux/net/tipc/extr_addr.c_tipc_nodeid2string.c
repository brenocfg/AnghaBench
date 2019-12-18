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
typedef  char u8 ;

/* Variables and functions */
 int NODE_ID_LEN ; 
 int NODE_ID_STR_LEN ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

char *tipc_nodeid2string(char *str, u8 *id)
{
	int i;
	u8 c;

	/* Already a string ? */
	for (i = 0; i < NODE_ID_LEN; i++) {
		c = id[i];
		if (c >= '0' && c <= '9')
			continue;
		if (c >= 'A' && c <= 'Z')
			continue;
		if (c >= 'a' && c <= 'z')
			continue;
		if (c == '.')
			continue;
		if (c == ':')
			continue;
		if (c == '_')
			continue;
		if (c == '-')
			continue;
		if (c == '@')
			continue;
		if (c != 0)
			break;
	}
	if (i == NODE_ID_LEN) {
		memcpy(str, id, NODE_ID_LEN);
		str[NODE_ID_LEN] = 0;
		return str;
	}

	/* Translate to hex string */
	for (i = 0; i < NODE_ID_LEN; i++)
		sprintf(&str[2 * i], "%02x", id[i]);

	/* Strip off trailing zeroes */
	for (i = NODE_ID_STR_LEN - 2; str[i] == '0'; i--)
		str[i] = 0;

	return str;
}