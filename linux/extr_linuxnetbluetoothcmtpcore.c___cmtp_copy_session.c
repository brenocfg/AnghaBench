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
typedef  int u32 ;
struct cmtp_session {int flags; int /*<<< orphan*/  num; int /*<<< orphan*/  state; int /*<<< orphan*/  bdaddr; } ;
struct cmtp_conninfo {int flags; int /*<<< orphan*/  num; int /*<<< orphan*/  state; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMTP_LOOPBACK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cmtp_conninfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __cmtp_copy_session(struct cmtp_session *session, struct cmtp_conninfo *ci)
{
	u32 valid_flags = BIT(CMTP_LOOPBACK);
	memset(ci, 0, sizeof(*ci));
	bacpy(&ci->bdaddr, &session->bdaddr);

	ci->flags = session->flags & valid_flags;
	ci->state = session->state;

	ci->num = session->num;
}