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
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 int TEST_mem_eq (char**,int,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_sanity_null_zero(void)
{
    char *p;
    char bytes[sizeof(p)];

    /* Is NULL equivalent to all-bytes-zero? */
    p = NULL;
    memset(bytes, 0, sizeof(bytes));
    return TEST_mem_eq(&p, sizeof(p), bytes, sizeof(bytes));
}