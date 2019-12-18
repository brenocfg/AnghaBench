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
struct mg_q_msg {int type; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (struct mg_mgr*,int /*<<< orphan*/ ) ;} ;
struct mg_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  (* mg_init_cb ) (struct mg_mgr*) ;

/* Variables and functions */
#define  MG_Q_MSG_CB 128 
 scalar_t__ OSI_OK ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 scalar_t__ osi_MsgQRead (int /*<<< orphan*/ *,struct mg_q_msg*,int) ; 
 int /*<<< orphan*/  s_mg_q ; 
 int /*<<< orphan*/  stub1 (struct mg_mgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_task(void *arg) {
  struct mg_mgr mgr;
  mg_init_cb mg_init = (mg_init_cb) arg;
  mg_mgr_init(&mgr, NULL);
  mg_init(&mgr);
  while (1) {
    struct mg_q_msg msg;
    mg_mgr_poll(&mgr, 1);
    if (osi_MsgQRead(&s_mg_q, &msg, 1) != OSI_OK) continue;
    switch (msg.type) {
      case MG_Q_MSG_CB: {
        msg.cb(&mgr, msg.arg);
      }
    }
  }
}