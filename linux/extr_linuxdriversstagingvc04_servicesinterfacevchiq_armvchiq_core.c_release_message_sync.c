#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* remote; } ;
typedef  TYPE_2__ VCHIQ_STATE_T ;
struct TYPE_8__ {int /*<<< orphan*/  msgid; } ;
typedef  TYPE_3__ VCHIQ_HEADER_T ;
struct TYPE_6__ {int /*<<< orphan*/  sync_release; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_MSGID_PADDING ; 
 int /*<<< orphan*/  remote_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
release_message_sync(VCHIQ_STATE_T *state, VCHIQ_HEADER_T *header)
{
	header->msgid = VCHIQ_MSGID_PADDING;
	wmb();
	remote_event_signal(&state->remote->sync_release);
}