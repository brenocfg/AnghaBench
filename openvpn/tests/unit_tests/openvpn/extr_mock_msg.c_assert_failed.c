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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mock_assert (int,char const*,char const*,int) ; 

void
assert_failed(const char *filename, int line, const char *condition)
{
    mock_assert(false, condition ? condition : "", filename, line);
    /* Keep compiler happy.  Should not happen, mock_assert() does not return */
    exit(1);
}