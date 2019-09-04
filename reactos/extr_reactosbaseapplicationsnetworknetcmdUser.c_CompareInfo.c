#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  usri0_name; } ;
typedef  TYPE_1__* PUSER_INFO_0 ;

/* Variables and functions */
 int _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int
CompareInfo(const void *a, const void *b)
{
    return _wcsicmp(((PUSER_INFO_0)a)->usri0_name,
                    ((PUSER_INFO_0)b)->usri0_name);
}