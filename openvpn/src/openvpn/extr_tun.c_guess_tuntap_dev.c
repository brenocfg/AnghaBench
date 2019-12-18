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
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int const DEV_TYPE_TAP ; 
 int const DEV_TYPE_TUN ; 
 int dev_type_enum (char const*,char const*) ; 
 char const* netsh_get_id (char const*,struct gc_arena*) ; 

const char *
guess_tuntap_dev(const char *dev,
                 const char *dev_type,
                 const char *dev_node,
                 struct gc_arena *gc)
{
#ifdef _WIN32
    const int dt = dev_type_enum(dev, dev_type);
    if (dt == DEV_TYPE_TUN || dt == DEV_TYPE_TAP)
    {
        return netsh_get_id(dev_node, gc);
    }
#endif

    /* default case */
    return dev;
}