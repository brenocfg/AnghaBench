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
struct iscsi_tmr_req {int dummy; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int iscsit_task_reassign_prepare_read(
	struct iscsi_tmr_req *tmr_req,
	struct iscsi_conn *conn)
{
	return 0;
}