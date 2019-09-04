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
struct vo_x11_state {int dummy; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*) ; 
 scalar_t__ XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _NET_WM_STATE_ABOVE ; 
 int /*<<< orphan*/  _NET_WM_STATE_BELOW ; 
 int /*<<< orphan*/  _NET_WM_STATE_FULLSCREEN ; 
 int /*<<< orphan*/  _NET_WM_STATE_STAYS_ON_TOP ; 
 int vo_wm_ABOVE ; 
 int vo_wm_BELOW ; 
 int vo_wm_FULLSCREEN ; 
 int vo_wm_STAYS_ON_TOP ; 

__attribute__((used)) static int net_wm_support_state_test(struct vo_x11_state *x11, Atom atom)
{
#define NET_WM_STATE_TEST(x) { \
    if (atom == XA(x11, _NET_WM_STATE_##x)) { \
        MP_VERBOSE(x11, "Detected wm supports " #x " state.\n" ); \
        return vo_wm_##x; \
    } \
}

    NET_WM_STATE_TEST(FULLSCREEN);
    NET_WM_STATE_TEST(ABOVE);
    NET_WM_STATE_TEST(STAYS_ON_TOP);
    NET_WM_STATE_TEST(BELOW);
    return 0;
}