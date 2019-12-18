#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* location; } ;
typedef  TYPE_1__ ACCESS_DESCRIPTION ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_DESCRIPTION_free (TYPE_1__*) ; 
 TYPE_1__* ACCESS_DESCRIPTION_new () ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_1__*) ; 
 TYPE_1__* GENERAL_NAME_new () ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static int test_access_description(int testcase)
{
    ACCESS_DESCRIPTION *ad = ACCESS_DESCRIPTION_new();
    int ret = 0;

    if (!TEST_ptr(ad))
        goto err;

    switch (testcase) {
    case 0:     /* no change */
        break;
    case 1:     /* check and release current location */
        if (!TEST_ptr(ad->location))
            goto err;
        GENERAL_NAME_free(ad->location);
        ad->location = NULL;
        break;
    case 2:     /* replace current location */
        GENERAL_NAME_free(ad->location);
        ad->location = GENERAL_NAME_new();
        if (!TEST_ptr(ad->location))
            goto err;
        break;
    }
    ACCESS_DESCRIPTION_free(ad);
    ret = 1;
err:
    return ret;
}