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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {scalar_t__ tx_hash; scalar_t__ rx_hash; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_free (scalar_t__) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_release_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_tcp_conn_teardown (struct iscsi_cls_conn*) ; 

__attribute__((used)) static void iscsi_sw_tcp_conn_destroy(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	iscsi_sw_tcp_release_conn(conn);

	ahash_request_free(tcp_sw_conn->rx_hash);
	if (tcp_sw_conn->tx_hash) {
		struct crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(tcp_sw_conn->tx_hash);
		ahash_request_free(tcp_sw_conn->tx_hash);
		crypto_free_ahash(tfm);
	}

	iscsi_tcp_conn_teardown(cls_conn);
}