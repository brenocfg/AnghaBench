#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ao {TYPE_1__* driver; int /*<<< orphan*/  stream_silence; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AO_STATE_PLAY ; 
 int /*<<< orphan*/  set_state (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ao*) ; 

__attribute__((used)) static void resume(struct ao *ao)
{
    set_state(ao, AO_STATE_PLAY);
    if (!ao->stream_silence)
        ao->driver->resume(ao);
}