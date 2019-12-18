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
 int /*<<< orphan*/  MP_FATAL (struct priv*,char*) ; 
 int /*<<< orphan*/  vsscript_init () ; 

__attribute__((used)) static int drv_vss_init(struct priv *p)
{
    if (!vsscript_init()) {
        MP_FATAL(p, "Could not initialize VapourSynth scripting.\n");
        return -1;
    }
    p->vs_initialized = true;
    return 0;
}