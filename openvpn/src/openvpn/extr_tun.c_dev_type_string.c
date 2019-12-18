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
#define  DEV_TYPE_NULL 130 
#define  DEV_TYPE_TAP 129 
#define  DEV_TYPE_TUN 128 
 int dev_type_enum (char const*,char const*) ; 

const char *
dev_type_string(const char *dev, const char *dev_type)
{
    switch (dev_type_enum(dev, dev_type))
    {
        case DEV_TYPE_TUN:
            return "tun";

        case DEV_TYPE_TAP:
            return "tap";

        case DEV_TYPE_NULL:
            return "null";

        default:
            return "[unknown-dev-type]";
    }
}