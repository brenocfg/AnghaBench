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
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 scalar_t__ BuildListOfServicesToStop (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

LPWSTR
GetListOfServicesToStop(LPWSTR lpServiceName)
{
    LPWSTR lpServiceList = NULL;

    /* Call recursive function to get our list */
    if (BuildListOfServicesToStop(&lpServiceList, lpServiceName))
        return lpServiceList;
    else
        return NULL;
}