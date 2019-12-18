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

/* Variables and functions */
 int /*<<< orphan*/  allow_customize ; 
 int call_malloc_debug ; 

int CRYPTO_set_mem_debug(int flag)
{
    if (!allow_customize)
        return 0;
    call_malloc_debug = flag;
    return 1;
}