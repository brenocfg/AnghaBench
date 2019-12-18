#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nocache; int wait_for_push; } ;
struct TYPE_3__ {int nocache; } ;

/* Variables and functions */
 TYPE_2__ auth_user_pass ; 
 TYPE_1__ passbuf ; 

void
ssl_set_auth_nocache(void)
{
    passbuf.nocache = true;
    auth_user_pass.nocache = true;
    /* wait for push-reply, because auth-token may still need the username */
    auth_user_pass.wait_for_push = true;
}