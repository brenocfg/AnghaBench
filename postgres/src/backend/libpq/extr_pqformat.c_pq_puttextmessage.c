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
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_server_to_client (char const*,int) ; 
 int /*<<< orphan*/  pq_putmessage (char,char const*,int) ; 
 int strlen (char const*) ; 

void
pq_puttextmessage(char msgtype, const char *str)
{
	int			slen = strlen(str);
	char	   *p;

	p = pg_server_to_client(str, slen);
	if (p != str)				/* actual conversion has been done? */
	{
		(void) pq_putmessage(msgtype, p, strlen(p) + 1);
		pfree(p);
		return;
	}
	(void) pq_putmessage(msgtype, str, slen + 1);
}