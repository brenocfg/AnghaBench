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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnep_session {int dummy; } ;
struct bnep_control_rsp {int /*<<< orphan*/  resp; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int /*<<< orphan*/  BNEP_CONTROL ; 
 int bnep_send (struct bnep_session*,struct bnep_control_rsp*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnep_send_rsp(struct bnep_session *s, u8 ctrl, u16 resp)
{
	struct bnep_control_rsp rsp;
	rsp.type = BNEP_CONTROL;
	rsp.ctrl = ctrl;
	rsp.resp = htons(resp);
	return bnep_send(s, &rsp, sizeof(rsp));
}