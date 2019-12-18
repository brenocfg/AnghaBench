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
struct priv {int /*<<< orphan*/ * vscore; int /*<<< orphan*/ * vsapi; int /*<<< orphan*/ * se; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsscript_freeScript (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drv_vss_unload(struct priv *p)
{
    if (p->se)
        vsscript_freeScript(p->se);
    p->se = NULL;
    p->vsapi = NULL;
    p->vscore = NULL;
}