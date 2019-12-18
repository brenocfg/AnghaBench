#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ st; int /*<<< orphan*/  ex_data; } ;
struct TYPE_8__ {char* hello; } ;
typedef  TYPE_1__ MYOBJ_EX_DATA ;
typedef  TYPE_2__ MYOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_APP ; 
 int /*<<< orphan*/  CRYPTO_alloc_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* CRYPTO_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (TYPE_1__*) ; 
 scalar_t__ TEST_ptr_null (TYPE_1__*) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 scalar_t__ gbl_result ; 
 int /*<<< orphan*/  saved_idx3 ; 

__attribute__((used)) static void MYOBJ_allochello3(MYOBJ *obj, char *cp)
{
    MYOBJ_EX_DATA* ex_data = NULL;

    if (TEST_ptr_null(ex_data = CRYPTO_get_ex_data(&obj->ex_data, saved_idx3))
        && TEST_true(CRYPTO_alloc_ex_data(CRYPTO_EX_INDEX_APP, obj,
                                          &obj->ex_data, saved_idx3))
        && TEST_ptr(ex_data = CRYPTO_get_ex_data(&obj->ex_data, saved_idx3)))
        ex_data->hello = cp;
    else
        obj->st = gbl_result = 0;
}