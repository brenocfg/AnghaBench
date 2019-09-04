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
struct iscsi_tcp_conn {struct cxgbi_conn* dd_data; } ;
struct iscsi_conn {unsigned int max_recv_dlength; struct iscsi_tcp_conn* dd_data; } ;
struct cxgbi_conn {TYPE_2__* chba; } ;
struct TYPE_4__ {TYPE_1__* cdev; } ;
struct TYPE_3__ {unsigned int rx_max_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cxgbi_align_pdu_size (unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int cxgbi_conn_max_recv_dlength(struct iscsi_conn *conn)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct cxgbi_conn *cconn = tcp_conn->dd_data;
	unsigned int max = cconn->chba->cdev->rx_max_size;

	cxgbi_align_pdu_size(max);

	if (conn->max_recv_dlength) {
		if (conn->max_recv_dlength > max) {
			pr_err("MaxRecvDataSegmentLength %u > %u.\n",
				conn->max_recv_dlength, max);
			return -EINVAL;
		}
		conn->max_recv_dlength = min(conn->max_recv_dlength, max);
		cxgbi_align_pdu_size(conn->max_recv_dlength);
	} else
		conn->max_recv_dlength = max;

	return 0;
}