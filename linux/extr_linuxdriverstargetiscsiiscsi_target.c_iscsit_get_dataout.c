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
typedef  int u32 ;
struct kvec {int* iov_base; int iov_len; } ;
struct iscsi_data {int /*<<< orphan*/  datasn; int /*<<< orphan*/  offset; int /*<<< orphan*/  itt; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_rx_hash; TYPE_1__* conn_ops; } ;
struct iscsi_cmd {int* pad_bytes; struct kvec* iov_data; } ;
struct TYPE_2__ {scalar_t__ DataDigest; } ;

/* Variables and functions */
 int ISCSI_CRC_LEN ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int iscsit_do_crypto_hash_sg (int /*<<< orphan*/ ,struct iscsi_cmd*,int /*<<< orphan*/ ,int,int,int*) ; 
 int iscsit_map_iovec (struct iscsi_cmd*,struct kvec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iscsit_unmap_iovec (struct iscsi_cmd*) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int rx_data (struct iscsi_conn*,struct kvec*,int,int) ; 

__attribute__((used)) static int
iscsit_get_dataout(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
		   struct iscsi_data *hdr)
{
	struct kvec *iov;
	u32 checksum, iov_count = 0, padding = 0, rx_got = 0, rx_size = 0;
	u32 payload_length = ntoh24(hdr->dlength);
	int iov_ret, data_crc_failed = 0;

	rx_size += payload_length;
	iov = &cmd->iov_data[0];

	iov_ret = iscsit_map_iovec(cmd, iov, be32_to_cpu(hdr->offset),
				   payload_length);
	if (iov_ret < 0)
		return -1;

	iov_count += iov_ret;

	padding = ((-payload_length) & 3);
	if (padding != 0) {
		iov[iov_count].iov_base	= cmd->pad_bytes;
		iov[iov_count++].iov_len = padding;
		rx_size += padding;
		pr_debug("Receiving %u padding bytes.\n", padding);
	}

	if (conn->conn_ops->DataDigest) {
		iov[iov_count].iov_base = &checksum;
		iov[iov_count++].iov_len = ISCSI_CRC_LEN;
		rx_size += ISCSI_CRC_LEN;
	}

	rx_got = rx_data(conn, &cmd->iov_data[0], iov_count, rx_size);

	iscsit_unmap_iovec(cmd);

	if (rx_got != rx_size)
		return -1;

	if (conn->conn_ops->DataDigest) {
		u32 data_crc;

		data_crc = iscsit_do_crypto_hash_sg(conn->conn_rx_hash, cmd,
						    be32_to_cpu(hdr->offset),
						    payload_length, padding,
						    cmd->pad_bytes);

		if (checksum != data_crc) {
			pr_err("ITT: 0x%08x, Offset: %u, Length: %u,"
				" DataSN: 0x%08x, CRC32C DataDigest 0x%08x"
				" does not match computed 0x%08x\n",
				hdr->itt, hdr->offset, payload_length,
				hdr->datasn, checksum, data_crc);
			data_crc_failed = 1;
		} else {
			pr_debug("Got CRC32C DataDigest 0x%08x for"
				" %u bytes of Data Out\n", checksum,
				payload_length);
		}
	}

	return data_crc_failed;
}