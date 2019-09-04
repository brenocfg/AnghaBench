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
typedef  long long ut64 ;
struct r_bin_te_obj_t {TYPE_1__* header; } ;
struct TYPE_2__ {int /*<<< orphan*/  ImageBase; } ;

/* Variables and functions */

ut64 r_bin_te_get_image_base(struct r_bin_te_obj_t* bin)
{
	if (bin && bin->header) {
		return (ut64)bin->header->ImageBase;
	}
	return 0LL;
}