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
struct TYPE_3__ {int /*<<< orphan*/  options; scalar_t__ inc; int /*<<< orphan*/  const* end; int /*<<< orphan*/  const* pos; } ;
typedef  TYPE_1__ vle_handle ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  VLE_DEFAULTS ; 

int vle_init(vle_handle* handle, const ut8* buffer, const ut32 size) {
	if (!handle || !buffer || size < 2) {
		return 1;
	}
	handle->pos = buffer;
	handle->end = buffer + size;
	handle->inc = 0;
	handle->options = VLE_DEFAULTS;
	return 0;
}