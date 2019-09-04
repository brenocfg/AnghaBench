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
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_APPEND ; 
 int test_binary_concat_impl (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum test_return test_binary_append(void) {
    return test_binary_concat_impl("test_binary_append",
                                   PROTOCOL_BINARY_CMD_APPEND);
}