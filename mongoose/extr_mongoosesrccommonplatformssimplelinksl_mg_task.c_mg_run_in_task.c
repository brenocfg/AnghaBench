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
struct mg_q_msg {void (* member_1 ) (struct mg_mgr*,void*) ;void* member_2; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_Q_MSG_CB ; 
 int /*<<< orphan*/  OSI_NO_WAIT ; 
 int /*<<< orphan*/  osi_MsgQWrite (int /*<<< orphan*/ *,struct mg_q_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mg_q ; 

void mg_run_in_task(void (*cb)(struct mg_mgr *mgr, void *arg), void *cb_arg) {
  struct mg_q_msg msg = {MG_Q_MSG_CB, cb, cb_arg};
  osi_MsgQWrite(&s_mg_q, &msg, OSI_NO_WAIT);
}