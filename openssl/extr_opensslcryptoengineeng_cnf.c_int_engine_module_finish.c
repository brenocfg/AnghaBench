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
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  CONF_IMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * initialized_engines ; 
 int /*<<< orphan*/  sk_ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ENGINE_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void int_engine_module_finish(CONF_IMODULE *md)
{
    ENGINE *e;

    while ((e = sk_ENGINE_pop(initialized_engines)))
        ENGINE_finish(e);
    sk_ENGINE_free(initialized_engines);
    initialized_engines = NULL;
}