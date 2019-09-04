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
struct gl_video {TYPE_2__* ra; } ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* debug_marker ) (TYPE_2__*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*) ; 

__attribute__((used)) static void debug_check_gl(struct gl_video *p, const char *msg)
{
    if (p->ra->fns->debug_marker)
        p->ra->fns->debug_marker(p->ra, msg);
}