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
struct TYPE_2__ {int /*<<< orphan*/  frame_fragment; scalar_t__ fragment; int /*<<< orphan*/  frame; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MTU_INFO ; 
 int /*<<< orphan*/  frame_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_print_data_channel_mtu_parms(struct context *c)
{
    frame_print(&c->c2.frame, D_MTU_INFO, "Data Channel MTU parms");
#ifdef ENABLE_FRAGMENT
    if (c->c2.fragment)
    {
        frame_print(&c->c2.frame_fragment, D_MTU_INFO,
                    "Fragmentation MTU parms");
    }
#endif
}