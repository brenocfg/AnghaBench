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
#define  AF_INET 129 
#define  AF_INET6 128 

const char *
addr_family_name(int af)
{
    switch (af)
    {
        case AF_INET:  return "AF_INET";

        case AF_INET6: return "AF_INET6";
    }
    return "AF_UNSPEC";
}