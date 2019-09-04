#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ CIPHERLIST_TEST_FIXTURE ;

/* Variables and functions */
 scalar_t__ test_default_cipherlist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_test(CIPHERLIST_TEST_FIXTURE *fixture)
{
    return fixture != NULL
        && test_default_cipherlist(fixture->server)
        && test_default_cipherlist(fixture->client);
}