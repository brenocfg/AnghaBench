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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  pq_getmsgint64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgstring (int /*<<< orphan*/ ) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

char *
logicalrep_read_origin(StringInfo in, XLogRecPtr *origin_lsn)
{
	/* fixed fields */
	*origin_lsn = pq_getmsgint64(in);

	/* return origin */
	return pstrdup(pq_getmsgstring(in));
}