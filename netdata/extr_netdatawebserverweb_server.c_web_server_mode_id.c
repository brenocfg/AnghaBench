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
typedef  int /*<<< orphan*/  WEB_SERVER_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_SERVER_MODE_NONE ; 
 int /*<<< orphan*/  WEB_SERVER_MODE_STATIC_THREADED ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

WEB_SERVER_MODE web_server_mode_id(const char *mode) {
    if(!strcmp(mode, "none"))
        return WEB_SERVER_MODE_NONE;
    else
        return WEB_SERVER_MODE_STATIC_THREADED;

}