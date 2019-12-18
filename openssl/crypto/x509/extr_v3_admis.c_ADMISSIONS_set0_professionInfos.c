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
struct TYPE_3__ {int /*<<< orphan*/ * professionInfos; } ;
typedef  int /*<<< orphan*/  PROFESSION_INFOS ;
typedef  TYPE_1__ ADMISSIONS ;

/* Variables and functions */
 int /*<<< orphan*/  PROFESSION_INFO_free ; 
 int /*<<< orphan*/  sk_PROFESSION_INFO_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ADMISSIONS_set0_professionInfos(ADMISSIONS *a, PROFESSION_INFOS *pi)
{
    sk_PROFESSION_INFO_pop_free(a->professionInfos, PROFESSION_INFO_free);
    a->professionInfos = pi;
}