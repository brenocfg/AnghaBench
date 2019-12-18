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
 int _access (char const*,int) ; 
 int access (char const*,int) ; 

int app_access(const char* name, int flag)
{
#ifdef _WIN32
    return _access(name, flag);
#else
    return access(name, flag);
#endif
}