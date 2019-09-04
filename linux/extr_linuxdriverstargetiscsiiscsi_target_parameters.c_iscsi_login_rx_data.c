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
struct kvec {int iov_len; char* iov_base; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct kvec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int rx_data (struct iscsi_conn*,struct kvec*,int,int) ; 

int iscsi_login_rx_data(
	struct iscsi_conn *conn,
	char *buf,
	int length)
{
	int rx_got;
	struct kvec iov;

	memset(&iov, 0, sizeof(struct kvec));
	iov.iov_len	= length;
	iov.iov_base	= buf;

	rx_got = rx_data(conn, &iov, 1, length);
	if (rx_got != length) {
		pr_err("rx_data returned %d, expecting %d.\n",
				rx_got, length);
		return -1;
	}

	return 0 ;
}