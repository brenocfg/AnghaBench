#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct kvec {int iov_len; char* iov_base; } ;
struct iscsi_conn {TYPE_3__* conn_ops; TYPE_2__* sess; } ;
struct TYPE_6__ {scalar_t__ DataDigest; } ;
struct TYPE_5__ {TYPE_1__* sess_ops; } ;
struct TYPE_4__ {scalar_t__ RDMAExtensions; } ;

/* Variables and functions */
 int DATAOUT_CANNOT_RECOVER ; 
 int DATAOUT_WITHIN_COMMAND_RECOVERY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ISCSI_CRC_LEN ; 
 int OFFLOAD_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kvec*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rx_data (struct iscsi_conn*,struct kvec*,int,int) ; 

int iscsit_dump_data_payload(
	struct iscsi_conn *conn,
	u32 buf_len,
	int dump_padding_digest)
{
	char *buf, pad_bytes[4];
	int ret = DATAOUT_WITHIN_COMMAND_RECOVERY, rx_got;
	u32 length, padding, offset = 0, size;
	struct kvec iov;

	if (conn->sess->sess_ops->RDMAExtensions)
		return 0;

	length = min(buf_len, OFFLOAD_BUF_SIZE);

	buf = kzalloc(length, GFP_ATOMIC);
	if (!buf) {
		pr_err("Unable to allocate %u bytes for offload"
				" buffer.\n", length);
		return -1;
	}
	memset(&iov, 0, sizeof(struct kvec));

	while (offset < buf_len) {
		size = min(buf_len - offset, length);

		iov.iov_len = size;
		iov.iov_base = buf;

		rx_got = rx_data(conn, &iov, 1, size);
		if (rx_got != size) {
			ret = DATAOUT_CANNOT_RECOVER;
			goto out;
		}

		offset += size;
	}

	if (!dump_padding_digest)
		goto out;

	padding = ((-buf_len) & 3);
	if (padding != 0) {
		iov.iov_len = padding;
		iov.iov_base = pad_bytes;

		rx_got = rx_data(conn, &iov, 1, padding);
		if (rx_got != padding) {
			ret = DATAOUT_CANNOT_RECOVER;
			goto out;
		}
	}

	if (conn->conn_ops->DataDigest) {
		u32 data_crc;

		iov.iov_len = ISCSI_CRC_LEN;
		iov.iov_base = &data_crc;

		rx_got = rx_data(conn, &iov, 1, ISCSI_CRC_LEN);
		if (rx_got != ISCSI_CRC_LEN) {
			ret = DATAOUT_CANNOT_RECOVER;
			goto out;
		}
	}

out:
	kfree(buf);
	return ret;
}