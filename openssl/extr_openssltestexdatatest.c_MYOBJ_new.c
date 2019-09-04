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
struct TYPE_5__ {int id; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  st; } ;
typedef  TYPE_1__ MYOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_APP ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 

__attribute__((used)) static MYOBJ *MYOBJ_new(void)
{
    static int count = 0;
    MYOBJ *obj = OPENSSL_malloc(sizeof(*obj));

    obj->id = ++count;
    obj->st = CRYPTO_new_ex_data(CRYPTO_EX_INDEX_APP, obj, &obj->ex_data);
    return obj;
}