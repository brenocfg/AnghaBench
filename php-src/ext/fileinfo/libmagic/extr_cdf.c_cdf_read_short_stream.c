#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * sst_tab; } ;
typedef  TYPE_1__ cdf_stream_t ;
typedef  int /*<<< orphan*/  cdf_sat_t ;
typedef  int /*<<< orphan*/  cdf_info_t ;
typedef  int /*<<< orphan*/  cdf_header_t ;
struct TYPE_10__ {scalar_t__ d_type; scalar_t__ d_stream_first_sector; int /*<<< orphan*/  d_size; } ;
typedef  TYPE_2__ cdf_directory_t ;
struct TYPE_11__ {size_t dir_len; TYPE_2__* dir_tab; } ;
typedef  TYPE_3__ cdf_dir_t ;

/* Variables and functions */
 scalar_t__ CDF_DIR_TYPE_ROOT_STORAGE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int cdf_read_long_sector_chain (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cdf_zero_stream (TYPE_1__*) ; 

int
cdf_read_short_stream(const cdf_info_t *info, const cdf_header_t *h,
    const cdf_sat_t *sat, const cdf_dir_t *dir, cdf_stream_t *scn,
    const cdf_directory_t **root)
{
	size_t i;
	const cdf_directory_t *d;

	*root = NULL;
	for (i = 0; i < dir->dir_len; i++)
		if (dir->dir_tab[i].d_type == CDF_DIR_TYPE_ROOT_STORAGE)
			break;

	/* If the it is not there, just fake it; some docs don't have it */
	if (i == dir->dir_len) {
		DPRINTF(("Cannot find root storage dir\n"));
		goto out;
	}
	d = &dir->dir_tab[i];
	*root = d;

	/* If the it is not there, just fake it; some docs don't have it */
	if (d->d_stream_first_sector < 0) {
		DPRINTF(("No first secror in dir\n"));
		goto out;
	}

	return cdf_read_long_sector_chain(info, h, sat,
	    d->d_stream_first_sector, d->d_size, scn);
out:
	scn->sst_tab = NULL;
	(void)cdf_zero_stream(scn);
	return 0;
}