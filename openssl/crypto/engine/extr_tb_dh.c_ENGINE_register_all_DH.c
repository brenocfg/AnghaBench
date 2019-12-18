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

/* Variables and functions */
 int /*<<< orphan*/ * ENGINE_get_first () ; 
 int /*<<< orphan*/ * ENGINE_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_DH (int /*<<< orphan*/ *) ; 

void ENGINE_register_all_DH(void)
{
    ENGINE *e;

    for (e = ENGINE_get_first(); e; e = ENGINE_get_next(e))
        ENGINE_register_DH(e);
}