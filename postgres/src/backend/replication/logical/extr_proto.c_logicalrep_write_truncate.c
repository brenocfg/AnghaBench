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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int Oid ;

/* Variables and functions */
 int /*<<< orphan*/  TRUNCATE_CASCADE ; 
 int /*<<< orphan*/  TRUNCATE_RESTART_SEQS ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
logicalrep_write_truncate(StringInfo out,
						  int nrelids,
						  Oid relids[],
						  bool cascade, bool restart_seqs)
{
	int			i;
	uint8		flags = 0;

	pq_sendbyte(out, 'T');		/* action TRUNCATE */

	pq_sendint32(out, nrelids);

	/* encode and send truncate flags */
	if (cascade)
		flags |= TRUNCATE_CASCADE;
	if (restart_seqs)
		flags |= TRUNCATE_RESTART_SEQS;
	pq_sendint8(out, flags);

	for (i = 0; i < nrelids; i++)
		pq_sendint32(out, relids[i]);
}