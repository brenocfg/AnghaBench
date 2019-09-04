#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_errhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  cause; } ;
struct TYPE_2__ {int /*<<< orphan*/  err_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; int /*<<< orphan*/  skb; } ;
typedef  int /*<<< orphan*/  err ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_errhdr*) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

int sctp_init_cause(struct sctp_chunk *chunk, __be16 cause_code,
		    size_t paylen)
{
	struct sctp_errhdr err;
	__u16 len;

	/* Cause code constants are now defined in network order.  */
	err.cause = cause_code;
	len = sizeof(err) + paylen;
	err.length = htons(len);

	if (skb_tailroom(chunk->skb) < len)
		return -ENOSPC;

	chunk->subh.err_hdr = sctp_addto_chunk(chunk, sizeof(err), &err);

	return 0;
}