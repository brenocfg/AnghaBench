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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendBinaryStringInfoNT (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_server_to_client (char const*,int) ; 
 int strlen (char const*) ; 

void
pq_sendstring(StringInfo buf, const char *str)
{
	int			slen = strlen(str);
	char	   *p;

	p = pg_server_to_client(str, slen);
	if (p != str)				/* actual conversion has been done? */
	{
		slen = strlen(p);
		appendBinaryStringInfoNT(buf, p, slen + 1);
		pfree(p);
	}
	else
		appendBinaryStringInfoNT(buf, str, slen + 1);
}