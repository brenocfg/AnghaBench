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
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int* error_code ; 
 int /*<<< orphan*/ * error_msg ; 
 size_t num_errors ; 

__attribute__((used)) static void push_error(int code, LPCWSTR msg)
{
    if (num_errors < ARRAY_SIZE(error_code))
    {
        error_code[num_errors] = code;
        error_msg[num_errors] = msg;
        num_errors++;
    }
}