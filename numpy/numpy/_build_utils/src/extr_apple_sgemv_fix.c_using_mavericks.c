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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int 
using_mavericks() 
{
    int r;
    char str[32] = {0};
    size_t size = sizeof(str);
    r = sysctlbyname("kern.osproductversion", str, &size, NULL, 0);
    if ( r == 0 && strncmp(str, "10.9", strlen("10.9")) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}