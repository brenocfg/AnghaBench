#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int class_size; } ;
struct TYPE_7__ {TYPE_2__* classes; TYPE_1__ header; } ;
struct TYPE_6__ {int class_id; } ;
typedef  TYPE_3__ RBinDexObj ;

/* Variables and functions */

__attribute__((used)) static bool is_class_idx_in_code_classes(RBinDexObj *bin, int class_idx) {
	int i;
	for (i = 0; i < bin->header.class_size; i++) {
		if (class_idx == bin->classes[i].class_id) {
			return true;
		}
	}
	return false;
}