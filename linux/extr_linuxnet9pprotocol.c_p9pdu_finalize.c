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
struct p9_fcall {int size; int /*<<< orphan*/  tag; int /*<<< orphan*/  id; } ;
struct p9_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p9pdu_writef (struct p9_fcall*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,struct p9_fcall*) ; 

int p9pdu_finalize(struct p9_client *clnt, struct p9_fcall *pdu)
{
	int size = pdu->size;
	int err;

	pdu->size = 0;
	err = p9pdu_writef(pdu, 0, "d", size);
	pdu->size = size;

	trace_9p_protocol_dump(clnt, pdu);
	p9_debug(P9_DEBUG_9P, ">>> size=%d type: %d tag: %d\n",
		 pdu->size, pdu->id, pdu->tag);

	return err;
}