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
struct iscsi_data {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int iscsit_check_dataout_hdr (struct iscsi_conn*,unsigned char*,struct iscsi_cmd**) ; 
 int iscsit_check_dataout_payload (struct iscsi_cmd*,struct iscsi_data*,int) ; 
 int iscsit_get_dataout (struct iscsi_conn*,struct iscsi_cmd*,struct iscsi_data*) ; 

__attribute__((used)) static int iscsit_handle_data_out(struct iscsi_conn *conn, unsigned char *buf)
{
	struct iscsi_cmd *cmd = NULL;
	struct iscsi_data *hdr = (struct iscsi_data *)buf;
	int rc;
	bool data_crc_failed = false;

	rc = iscsit_check_dataout_hdr(conn, buf, &cmd);
	if (rc < 0)
		return 0;
	else if (!cmd)
		return 0;

	rc = iscsit_get_dataout(conn, cmd, hdr);
	if (rc < 0)
		return rc;
	else if (rc > 0)
		data_crc_failed = true;

	return iscsit_check_dataout_payload(cmd, hdr, data_crc_failed);
}