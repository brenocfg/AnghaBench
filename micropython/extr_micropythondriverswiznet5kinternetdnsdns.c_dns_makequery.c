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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ cp ;

/* Variables and functions */
 int DNS_MSGID ; 
 int MAXCNAME ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * put16 (int /*<<< orphan*/ *,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int16_t dns_makequery(uint16_t op, char * name, uint8_t * buf, uint16_t len)
{
	uint8_t *cp;
	char *cp1;
	char sname[MAXCNAME];
	char *dname;
	uint16_t p;
	uint16_t dlen;

	cp = buf;

	DNS_MSGID++;
	cp = put16(cp, DNS_MSGID);
	p = (op << 11) | 0x0100;			/* Recursion desired */
	cp = put16(cp, p);
	cp = put16(cp, 1);
	cp = put16(cp, 0);
	cp = put16(cp, 0);
	cp = put16(cp, 0);

	strcpy(sname, name);
	dname = sname;
	dlen = strlen(dname);
	for (;;)
	{
		/* Look for next dot */
		cp1 = strchr(dname, '.');

		if (cp1 != NULL) len = cp1 - dname;	/* More to come */
		else len = dlen;			/* Last component */

		*cp++ = len;				/* Write length of component */
		if (len == 0) break;

		/* Copy component up to (but not including) dot */
		memcpy(cp, dname, len);
		cp += len;
		if (cp1 == NULL)
		{
			*cp++ = 0;			/* Last one; write null and finish */
			break;
		}
		dname += len+1;
		dlen -= len+1;
	}

	cp = put16(cp, 0x0001);				/* type */
	cp = put16(cp, 0x0001);				/* class */

	return ((int16_t)((uint32_t)(cp) - (uint32_t)(buf)));
}