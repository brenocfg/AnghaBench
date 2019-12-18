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
struct bpf_sock_addr {scalar_t__ type; int msg_src_ip4; int user_ip4; scalar_t__ user_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_IP4 ; 
 int /*<<< orphan*/  DST_PORT ; 
 int /*<<< orphan*/  DST_REWRITE_IP4 ; 
 int /*<<< orphan*/  DST_REWRITE_PORT4 ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SRC1_IP4 ; 
 int /*<<< orphan*/  SRC2_IP4 ; 
 int /*<<< orphan*/  SRC_REWRITE_IP4 ; 
 int bpf_htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_htons (int /*<<< orphan*/ ) ; 

int sendmsg_v4_prog(struct bpf_sock_addr *ctx)
{
	if (ctx->type != SOCK_DGRAM)
		return 0;

	/* Rewrite source. */
	if (ctx->msg_src_ip4 == bpf_htonl(SRC1_IP4) ||
	    ctx->msg_src_ip4 == bpf_htonl(SRC2_IP4)) {
		ctx->msg_src_ip4 = bpf_htonl(SRC_REWRITE_IP4);
	} else {
		/* Unexpected source. Reject sendmsg. */
		return 0;
	}

	/* Rewrite destination. */
	if ((ctx->user_ip4 >> 24) == (bpf_htonl(DST_IP4) >> 24) &&
	     ctx->user_port == bpf_htons(DST_PORT)) {
		ctx->user_ip4 = bpf_htonl(DST_REWRITE_IP4);
		ctx->user_port = bpf_htons(DST_REWRITE_PORT4);
	} else {
		/* Unexpected source. Reject sendmsg. */
		return 0;
	}

	return 1;
}