#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pmod; } ;
typedef  int /*<<< orphan*/  CONF_MODULE ;
typedef  TYPE_1__ CONF_IMODULE ;

/* Variables and functions */

CONF_MODULE *CONF_imodule_get_module(const CONF_IMODULE *md)
{
    return md->pmod;
}