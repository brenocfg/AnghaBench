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
typedef  int /*<<< orphan*/  u32 ;
struct iscsi_datain_req {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int iscsit_xmit_datain_pdu (struct iscsi_conn*,struct iscsi_cmd*,void const*) ; 
 int iscsit_xmit_nondatain_pdu (struct iscsi_conn*,struct iscsi_cmd*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_xmit_pdu(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
			   struct iscsi_datain_req *dr, const void *buf,
			   u32 buf_len)
{
	if (dr)
		return iscsit_xmit_datain_pdu(conn, cmd, buf);
	else
		return iscsit_xmit_nondatain_pdu(conn, cmd, buf, buf_len);
}