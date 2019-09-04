#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  session_id; } ;
typedef  TYPE_1__ nfs41_session ;
struct TYPE_7__ {int /*<<< orphan*/  sa_cachethis; int /*<<< orphan*/  sa_sessionid; int /*<<< orphan*/  sa_highest_slotid; int /*<<< orphan*/  sa_sequenceid; int /*<<< orphan*/  sa_slotid; } ;
typedef  TYPE_2__ nfs41_sequence_args ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs41_session_get_slot (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nfs41_session_sequence(
    nfs41_sequence_args *args,
    nfs41_session *session,
    bool_t cachethis)
{
    nfs41_session_get_slot(session, &args->sa_slotid, 
        &args->sa_sequenceid, &args->sa_highest_slotid);
    args->sa_sessionid = session->session_id;
    args->sa_cachethis = cachethis;
}