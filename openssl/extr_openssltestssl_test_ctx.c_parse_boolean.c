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
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int parse_boolean(const char *value, int *result)
{
    if (strcasecmp(value, "Yes") == 0) {
        *result = 1;
        return 1;
    }
    else if (strcasecmp(value, "No") == 0) {
        *result = 0;
        return 1;
    }
    TEST_error("parse_boolean given: '%s'", value);
    return 0;
}