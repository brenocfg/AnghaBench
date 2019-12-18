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
struct virtual_output {int dummy; } ;

/* Variables and functions */
 struct virtual_output const* x_msg_virtual_output ; 

__attribute__((used)) static inline const struct virtual_output *
msg_get_virtual_output(void)
{
    return x_msg_virtual_output;
}