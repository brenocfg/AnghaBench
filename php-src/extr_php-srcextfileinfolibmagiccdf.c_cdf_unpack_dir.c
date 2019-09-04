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
struct TYPE_3__ {int /*<<< orphan*/  d_unused0; int /*<<< orphan*/  d_size; int /*<<< orphan*/  d_stream_first_sector; int /*<<< orphan*/  d_modified; int /*<<< orphan*/  d_created; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_storage_uuid; int /*<<< orphan*/  d_storage; int /*<<< orphan*/  d_right_child; int /*<<< orphan*/  d_left_child; int /*<<< orphan*/  d_color; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_namelen; int /*<<< orphan*/  d_name; } ;
typedef  TYPE_1__ cdf_directory_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDF_UNPACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDF_UNPACKA (int /*<<< orphan*/ ) ; 

void
cdf_unpack_dir(cdf_directory_t *d, char *buf)
{
	size_t len = 0;

	CDF_UNPACKA(d->d_name);
	CDF_UNPACK(d->d_namelen);
	CDF_UNPACK(d->d_type);
	CDF_UNPACK(d->d_color);
	CDF_UNPACK(d->d_left_child);
	CDF_UNPACK(d->d_right_child);
	CDF_UNPACK(d->d_storage);
	CDF_UNPACKA(d->d_storage_uuid);
	CDF_UNPACK(d->d_flags);
	CDF_UNPACK(d->d_created);
	CDF_UNPACK(d->d_modified);
	CDF_UNPACK(d->d_stream_first_sector);
	CDF_UNPACK(d->d_size);
	CDF_UNPACK(d->d_unused0);
}