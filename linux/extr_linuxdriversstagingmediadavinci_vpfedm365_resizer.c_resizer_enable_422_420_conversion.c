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
struct resizer_params {TYPE_1__* rsz_rsc_param; } ;
struct TYPE_2__ {int cen; int yen; } ;

/* Variables and functions */

__attribute__((used)) static void resizer_enable_422_420_conversion(struct resizer_params *param,
					      int index, bool en)
{
	param->rsz_rsc_param[index].cen = en;
	param->rsz_rsc_param[index].yen = en;
}