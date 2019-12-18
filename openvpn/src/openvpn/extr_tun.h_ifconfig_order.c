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
 int IFCONFIG_AFTER_TUN_OPEN ; 
 int IFCONFIG_BEFORE_TUN_OPEN ; 
 int IFCONFIG_DEFAULT ; 

__attribute__((used)) static inline int
ifconfig_order(void)
{
#if defined(TARGET_LINUX)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(TARGET_SOLARIS)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(TARGET_OPENBSD)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(TARGET_DARWIN)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(TARGET_NETBSD)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(_WIN32)
    return IFCONFIG_AFTER_TUN_OPEN;
#elif defined(TARGET_ANDROID)
    return IFCONFIG_BEFORE_TUN_OPEN;
#else  /* if defined(TARGET_LINUX) */
    return IFCONFIG_DEFAULT;
#endif
}