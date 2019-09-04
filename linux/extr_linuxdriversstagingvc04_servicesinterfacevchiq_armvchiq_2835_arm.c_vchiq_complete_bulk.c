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
struct vchiq_pagelist_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ actual; scalar_t__ remote_data; } ;
typedef  TYPE_1__ VCHIQ_BULK_T ;

/* Variables and functions */
 int /*<<< orphan*/  free_pagelist (struct vchiq_pagelist_info*,scalar_t__) ; 

void
vchiq_complete_bulk(VCHIQ_BULK_T *bulk)
{
	if (bulk && bulk->remote_data && bulk->actual)
		free_pagelist((struct vchiq_pagelist_info *)bulk->remote_data,
			      bulk->actual);
}