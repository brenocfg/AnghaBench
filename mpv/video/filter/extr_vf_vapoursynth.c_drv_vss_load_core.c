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
struct priv {int /*<<< orphan*/  se; int /*<<< orphan*/  vscore; int /*<<< orphan*/  vsapi; } ;

/* Variables and functions */
 scalar_t__ vsscript_createScript (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsscript_getCore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsscript_getVSApi () ; 

__attribute__((used)) static int drv_vss_load_core(struct priv *p)
{
    // First load an empty script to get a VSScript, so that we get the vsapi
    // and vscore.
    if (vsscript_createScript(&p->se))
        return -1;
    p->vsapi = vsscript_getVSApi();
    p->vscore = vsscript_getCore(p->se);
    return 0;
}