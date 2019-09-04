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
struct vc_data {int /*<<< orphan*/ * vc_palette; } ;

/* Variables and functions */
 int /*<<< orphan*/ * default_blu ; 
 int /*<<< orphan*/ * default_grn ; 
 int /*<<< orphan*/ * default_red ; 
 int /*<<< orphan*/  set_palette (struct vc_data*) ; 

void reset_palette(struct vc_data *vc)
{
	int j, k;
	for (j=k=0; j<16; j++) {
		vc->vc_palette[k++] = default_red[j];
		vc->vc_palette[k++] = default_grn[j];
		vc->vc_palette[k++] = default_blu[j];
	}
	set_palette(vc);
}