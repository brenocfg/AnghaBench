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
struct sk_buff {scalar_t__ len; } ;
struct iscsi_conn {int dummy; } ;
struct TYPE_4__ {struct iscsi_conn* data; } ;
struct TYPE_5__ {TYPE_1__ arg; } ;
typedef  TYPE_2__ read_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SW_TCP_DBG (struct iscsi_conn*,char*,scalar_t__,...) ; 
 int ISCSI_TCP_SKB_DONE ; 
 unsigned int iscsi_tcp_recv_skb (struct iscsi_conn*,struct sk_buff*,unsigned int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int iscsi_sw_tcp_recv(read_descriptor_t *rd_desc, struct sk_buff *skb,
			     unsigned int offset, size_t len)
{
	struct iscsi_conn *conn = rd_desc->arg.data;
	unsigned int consumed, total_consumed = 0;
	int status;

	ISCSI_SW_TCP_DBG(conn, "in %d bytes\n", skb->len - offset);

	do {
		status = 0;
		consumed = iscsi_tcp_recv_skb(conn, skb, offset, 0, &status);
		offset += consumed;
		total_consumed += consumed;
	} while (consumed != 0 && status != ISCSI_TCP_SKB_DONE);

	ISCSI_SW_TCP_DBG(conn, "read %d bytes status %d\n",
			 skb->len - offset, status);
	return total_consumed;
}