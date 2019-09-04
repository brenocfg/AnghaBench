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
typedef  int /*<<< orphan*/  test ;
struct Range {int begin; int end; } ;

/* Variables and functions */
 int count_cidr_bits (struct Range) ; 
 scalar_t__ masscan_conf_contains (char*,int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  trim (char*,int) ; 

int
mainconf_selftest()
{
    char test[] = " test 1 ";

    trim(test, sizeof(test));
    if (strcmp(test, "test 1") != 0)
        return 1; /* failure */

    {
        struct Range range;

        range.begin = 16;
        range.end = 32-1;
        if (count_cidr_bits(range) != 28)
            return 1;

        range.begin = 1;
        range.end = 13;
        if (count_cidr_bits(range) != 0)
            return 1;


    }

    /* */
    {
        int argc = 6;
        char *argv[] = { "foo", "bar", "-ddd", "--readscan", "xxx", "--something" };
    
        if (masscan_conf_contains("--nothing", argc, argv))
            return 1;

        if (!masscan_conf_contains("--readscan", argc, argv))
            return 1;
    }

    return 0;
}