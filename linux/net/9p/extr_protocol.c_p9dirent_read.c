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
struct p9_fcall {int size; int capacity; char* sdata; int offset; } ;
struct p9_dirent {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_off; int /*<<< orphan*/  qid; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
 int p9pdu_readf (struct p9_fcall*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,struct p9_fcall*) ; 

int p9dirent_read(struct p9_client *clnt, char *buf, int len,
		  struct p9_dirent *dirent)
{
	struct p9_fcall fake_pdu;
	int ret;
	char *nameptr;

	fake_pdu.size = len;
	fake_pdu.capacity = len;
	fake_pdu.sdata = buf;
	fake_pdu.offset = 0;

	ret = p9pdu_readf(&fake_pdu, clnt->proto_version, "Qqbs", &dirent->qid,
			  &dirent->d_off, &dirent->d_type, &nameptr);
	if (ret) {
		p9_debug(P9_DEBUG_9P, "<<< p9dirent_read failed: %d\n", ret);
		trace_9p_protocol_dump(clnt, &fake_pdu);
		return ret;
	}

	ret = strscpy(dirent->d_name, nameptr, sizeof(dirent->d_name));
	if (ret < 0) {
		p9_debug(P9_DEBUG_ERROR,
			 "On the wire dirent name too long: %s\n",
			 nameptr);
		kfree(nameptr);
		return ret;
	}
	kfree(nameptr);

	return fake_pdu.offset;
}