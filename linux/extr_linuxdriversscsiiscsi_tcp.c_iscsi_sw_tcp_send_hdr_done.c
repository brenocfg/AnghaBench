#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_tcp_conn {int /*<<< orphan*/  iscsi_conn; struct iscsi_sw_tcp_conn* dd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_size; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ segment; TYPE_1__ data_segment; } ;
struct iscsi_sw_tcp_conn {TYPE_2__ out; } ;
struct iscsi_segment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SW_TCP_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_sw_tcp_send_hdr_done(struct iscsi_tcp_conn *tcp_conn,
				      struct iscsi_segment *segment)
{
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	tcp_sw_conn->out.segment = tcp_sw_conn->out.data_segment;
	ISCSI_SW_TCP_DBG(tcp_conn->iscsi_conn,
			 "Header done. Next segment size %u total_size %u\n",
			 tcp_sw_conn->out.segment.size,
			 tcp_sw_conn->out.segment.total_size);
	return 0;
}