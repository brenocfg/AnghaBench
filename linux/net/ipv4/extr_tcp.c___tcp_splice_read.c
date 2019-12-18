#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_splice_state {int /*<<< orphan*/  len; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {struct tcp_splice_state* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;

/* Variables and functions */
 int tcp_read_sock (struct sock*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_splice_data_recv ; 

__attribute__((used)) static int __tcp_splice_read(struct sock *sk, struct tcp_splice_state *tss)
{
	/* Store TCP splice context information in read_descriptor_t. */
	read_descriptor_t rd_desc = {
		.arg.data = tss,
		.count	  = tss->len,
	};

	return tcp_read_sock(sk, &rd_desc, tcp_splice_data_recv);
}