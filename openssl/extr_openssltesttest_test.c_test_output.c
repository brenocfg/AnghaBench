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
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  test_output_memory (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  test_output_string (char*,char const*,int) ; 

__attribute__((used)) static int test_output(void)
{
    const char s[] = "1234567890123456789012345678901234567890123456789012"
                     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    test_output_string("test", s, sizeof(s) - 1);
    test_output_memory("test", (const unsigned char *)s, sizeof(s));
    return 1;
}