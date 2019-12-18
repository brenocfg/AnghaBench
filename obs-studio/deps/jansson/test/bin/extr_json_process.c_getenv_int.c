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
 char* getenv (char const*) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int getenv_int(const char *name)
{
    char *value, *end;
    long result;

    value = getenv(name);
    if(!value)
        return 0;

    result = strtol(value, &end, 10);
    if(*end != '\0')
        return 0;

    return (int)result;
}