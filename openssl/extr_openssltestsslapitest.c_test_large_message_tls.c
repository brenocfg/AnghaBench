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
 int /*<<< orphan*/  TLS1_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int execute_test_large_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_large_message_tls(void)
{
    return execute_test_large_message(TLS_server_method(), TLS_client_method(),
                                      TLS1_VERSION, 0, 0);
}