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
typedef  int /*<<< orphan*/  CONF_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  WIN32_method ; 

CONF_METHOD *NCONF_WIN32(void)
{
    return &WIN32_method;
}