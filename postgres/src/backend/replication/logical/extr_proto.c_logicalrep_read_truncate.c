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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int TRUNCATE_CASCADE ; 
 int TRUNCATE_RESTART_SEQS ; 
 int /*<<< orphan*/ * lappend_oid (int /*<<< orphan*/ *,void*) ; 
 void* pq_getmsgint (int /*<<< orphan*/ ,int) ; 

List *
logicalrep_read_truncate(StringInfo in,
						 bool *cascade, bool *restart_seqs)
{
	int			i;
	int			nrelids;
	List	   *relids = NIL;
	uint8		flags;

	nrelids = pq_getmsgint(in, 4);

	/* read and decode truncate flags */
	flags = pq_getmsgint(in, 1);
	*cascade = (flags & TRUNCATE_CASCADE) > 0;
	*restart_seqs = (flags & TRUNCATE_RESTART_SEQS) > 0;

	for (i = 0; i < nrelids; i++)
		relids = lappend_oid(relids, pq_getmsgint(in, 4));

	return relids;
}