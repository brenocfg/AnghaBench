#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ oth; } ;
typedef  TYPE_1__ spl_filesystem_object ;
struct TYPE_6__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_2__ phar_archive_data ;

/* Variables and functions */

__attribute__((used)) static void phar_spl_foreign_clone(spl_filesystem_object *src, spl_filesystem_object *dst) /* {{{ */
{
	phar_archive_data *phar_data = (phar_archive_data *) dst->oth;

	if (!phar_data->is_persistent) {
		++(phar_data->refcount);
	}
}