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
 unsigned int x_cs_err_delay_ms ; 

__attribute__((used)) static inline void
set_check_status_error_delay(unsigned int milliseconds)
{
    x_cs_err_delay_ms = milliseconds;
}