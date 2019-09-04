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
struct iscsi_np {int dummy; } ;
struct iscsi_login {int zero_tsih; struct iscsi_np* np; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_remove_failed_auth_entry (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_target_login_sess_out (struct iscsi_conn*,struct iscsi_np*,int,int) ; 
 int /*<<< orphan*/  iscsi_target_nego_release (struct iscsi_conn*) ; 

__attribute__((used)) static void iscsi_target_login_drop(struct iscsi_conn *conn, struct iscsi_login *login)
{
	struct iscsi_np *np = login->np;
	bool zero_tsih = login->zero_tsih;

	iscsi_remove_failed_auth_entry(conn);
	iscsi_target_nego_release(conn);
	iscsi_target_login_sess_out(conn, np, zero_tsih, true);
}