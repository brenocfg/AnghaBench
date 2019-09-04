#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ex_data; int /*<<< orphan*/  st; } ;
typedef  TYPE_1__ MYOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_APP ; 
 int /*<<< orphan*/  CRYPTO_dup_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* MYOBJ_new () ; 

__attribute__((used)) static MYOBJ *MYOBJ_dup(MYOBJ *in)
{
    MYOBJ *obj = MYOBJ_new();

    obj->st |= CRYPTO_dup_ex_data(CRYPTO_EX_INDEX_APP, &obj->ex_data,
                                 &in->ex_data);
    return obj;
}