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
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

void
pq_sendcountedtext(StringInfo buf, const char *str, int slen,
				   bool countincludesself)
{
	int			extra = countincludesself ? 4 : 0;
	char	   *p;

	p = pg_server_to_client(str, slen);
	if (p != str)				/* actual conversion has been done? */
	{
		slen = strlen(p);
		pq_sendint32(buf, slen + extra);
		appendBinaryStringInfoNT(buf, p, slen);
		pfree(p);
	}
	else
	{
		pq_sendint32(buf, slen + extra);
		appendBinaryStringInfoNT(buf, str, slen);
	}
}