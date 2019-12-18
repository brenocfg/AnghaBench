#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wifi_join_state; } ;
typedef  TYPE_1__ cyw43_t ;

/* Variables and functions */
 int CYW43_ITF_STA ; 
 int CYW43_LINK_BADAUTH ; 
 int CYW43_LINK_DOWN ; 
 int CYW43_LINK_FAIL ; 
 int CYW43_LINK_JOIN ; 
 int CYW43_LINK_NONET ; 
 int WIFI_JOIN_STATE_ACTIVE ; 
 int WIFI_JOIN_STATE_BADAUTH ; 
 int WIFI_JOIN_STATE_FAIL ; 
 int WIFI_JOIN_STATE_NONET ; 

int cyw43_wifi_link_status(cyw43_t *self, int itf) {
    if (itf == CYW43_ITF_STA) {
        int s = self->wifi_join_state & 0xf;
        if (s == WIFI_JOIN_STATE_ACTIVE) {
            return CYW43_LINK_JOIN;
        } else if (s == WIFI_JOIN_STATE_FAIL) {
            return CYW43_LINK_FAIL;
        } else if (s == WIFI_JOIN_STATE_NONET) {
            return CYW43_LINK_NONET;
        } else if (s == WIFI_JOIN_STATE_BADAUTH) {
            return CYW43_LINK_BADAUTH;
        } else {
            return CYW43_LINK_DOWN;
        }
    } else {
        return CYW43_LINK_DOWN;
    }
}