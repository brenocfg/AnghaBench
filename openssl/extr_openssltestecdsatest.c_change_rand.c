#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 TYPE_1__* RAND_get_rand_method () ; 
 int /*<<< orphan*/  RAND_set_rand_method (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__ fake_rand ; 
 int /*<<< orphan*/  fbytes ; 
 TYPE_1__* old_rand ; 

__attribute__((used)) static int change_rand(void)
{
    /* save old rand method */
    if (!TEST_ptr(old_rand = RAND_get_rand_method()))
        return 0;

    fake_rand = *old_rand;
    /* use own random function */
    fake_rand.bytes = fbytes;
    /* set new RAND_METHOD */
    if (!TEST_true(RAND_set_rand_method(&fake_rand)))
        return 0;
    return 1;
}