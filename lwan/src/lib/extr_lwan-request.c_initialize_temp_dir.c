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
 int /*<<< orphan*/  get_temp_dir () ; 
 int /*<<< orphan*/  temp_dir ; 

__attribute__((used)) __attribute__((constructor)) static void initialize_temp_dir(void)
{
    temp_dir = get_temp_dir();
}