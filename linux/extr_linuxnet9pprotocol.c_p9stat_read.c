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
struct p9_wstat {int dummy; } ;
struct p9_fcall {int size; int capacity; char* sdata; int offset; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int) ; 
 int p9pdu_readf (struct p9_fcall*,int /*<<< orphan*/ ,char*,struct p9_wstat*) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,struct p9_fcall*) ; 

int p9stat_read(struct p9_client *clnt, char *buf, int len, struct p9_wstat *st)
{
	struct p9_fcall fake_pdu;
	int ret;

	fake_pdu.size = len;
	fake_pdu.capacity = len;
	fake_pdu.sdata = buf;
	fake_pdu.offset = 0;

	ret = p9pdu_readf(&fake_pdu, clnt->proto_version, "S", st);
	if (ret) {
		p9_debug(P9_DEBUG_9P, "<<< p9stat_read failed: %d\n", ret);
		trace_9p_protocol_dump(clnt, &fake_pdu);
		return ret;
	}

	return fake_pdu.offset;
}