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
typedef  scalar_t__ int16_t ;
struct TYPE_2__ {scalar_t__ sd; } ;
typedef  int /*<<< orphan*/  SlFdSet_t ;

/* Variables and functions */
 int MOD_NETWORK_MAX_SOCKETS ; 
 int /*<<< orphan*/  SL_FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* modusocket_sockets ; 
 int /*<<< orphan*/  sl_Select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void modusocket_enter_sleep (void) {
    SlFdSet_t socketset;
    int16_t maxfd = 0;

    for (int i = 0; i < MOD_NETWORK_MAX_SOCKETS; i++) {
        int16_t sd;
        if ((sd = modusocket_sockets[i].sd) >= 0) {
            SL_FD_SET(sd, &socketset);
            maxfd = (maxfd > sd) ? maxfd : sd;
        }
    }

    if (maxfd > 0) {
        // wait for any of the sockets to become ready...
        sl_Select(maxfd + 1, &socketset, NULL, NULL, NULL);
    }
}