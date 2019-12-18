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
struct priv {int vs_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  vsscript_finalize () ; 

__attribute__((used)) static void drv_vss_uninit(struct priv *p)
{
    if (p->vs_initialized)
        vsscript_finalize();
    p->vs_initialized = false;
}