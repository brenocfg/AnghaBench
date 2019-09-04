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
 int /*<<< orphan*/  tc_device_free (scalar_t__) ; 
 scalar_t__ tc_device_root ; 

__attribute__((used)) static inline void tc_device_free_all()
{
    while(tc_device_root)
        tc_device_free(tc_device_root);
}