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
struct TYPE_3__ {int /*<<< orphan*/  st; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ MYOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 scalar_t__ gbl_result ; 
 int /*<<< orphan*/  saved_idx ; 

__attribute__((used)) static void MYOBJ_sethello(MYOBJ *obj, char *cp)
{
    obj->st = CRYPTO_set_ex_data(&obj->ex_data, saved_idx, cp);
    if (!TEST_int_eq(obj->st, 1))
        gbl_result = 0;
}