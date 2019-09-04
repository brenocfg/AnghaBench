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
typedef  int /*<<< orphan*/  mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup_client (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msg_wakeup(void *p)
{
    mpv_handle *ctx = p;
    wakeup_client(ctx);
}