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
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char const*) ; 

void
logicalrep_write_origin(StringInfo out, const char *origin,
						XLogRecPtr origin_lsn)
{
	pq_sendbyte(out, 'O');		/* ORIGIN */

	/* fixed fields */
	pq_sendint64(out, origin_lsn);

	/* origin string */
	pq_sendstring(out, origin);
}