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
typedef  int WEB_SERVER_MODE ;

/* Variables and functions */
#define  WEB_SERVER_MODE_NONE 129 
#define  WEB_SERVER_MODE_STATIC_THREADED 128 

const char *web_server_mode_name(WEB_SERVER_MODE id) {
    switch(id) {
        case WEB_SERVER_MODE_NONE:
            return "none";
        default:
        case WEB_SERVER_MODE_STATIC_THREADED:
            return "static-threaded";
    }
}