#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ctrl_t ;
struct TYPE_5__ {int /*<<< orphan*/  cached_getkey_kdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpg_dirmngr_deinit_session_data (TYPE_1__*) ; 
 int /*<<< orphan*/  keydb_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tofu_closedbs (TYPE_1__*) ; 

__attribute__((used)) static void
gpg_deinit_default_ctrl (ctrl_t ctrl)
{
#ifdef USE_TOFU
    tofu_closedbs (ctrl);
#endif
    gpg_dirmngr_deinit_session_data (ctrl);

    keydb_release (ctrl->cached_getkey_kdb);
}