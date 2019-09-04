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
struct MPContext {int dummy; } ;

/* Variables and functions */
 scalar_t__ run_next_hook_handler (struct MPContext*,char*,int /*<<< orphan*/ ) ; 

void mp_hook_start(struct MPContext *mpctx, char *type)
{
    while (run_next_hook_handler(mpctx, type, 0) < 0) {
        // We can repeat this until all broken clients have been removed, and
        // hook processing is successfully started.
    }
}