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
typedef  int SYS_MODULE_OBJ ;
typedef  int /*<<< orphan*/  SYS_MODULE_INIT ;
typedef  int /*<<< orphan*/  SYS_MODULE_INDEX ;

/* Variables and functions */

SYS_MODULE_OBJ SYS_CONSOLE_Initialize( const SYS_MODULE_INDEX index, const SYS_MODULE_INIT * const init )
{
    return 1;
}