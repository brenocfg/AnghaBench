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
struct TYPE_3__ {int /*<<< orphan*/ * h_master_sat; int /*<<< orphan*/  h_num_sectors_in_master_sat; int /*<<< orphan*/  h_secid_first_sector_in_master_sat; int /*<<< orphan*/  h_num_sectors_in_short_sat; int /*<<< orphan*/  h_secid_first_sector_in_short_sat; int /*<<< orphan*/  h_min_size_standard_stream; int /*<<< orphan*/  h_unused1; int /*<<< orphan*/  h_secid_first_directory; int /*<<< orphan*/  h_num_sectors_in_sat; int /*<<< orphan*/  h_unused0; int /*<<< orphan*/  h_short_sec_size_p2; int /*<<< orphan*/  h_sec_size_p2; int /*<<< orphan*/  h_byte_order; int /*<<< orphan*/  h_version; int /*<<< orphan*/  h_revision; int /*<<< orphan*/  h_uuid; int /*<<< orphan*/  h_magic; } ;
typedef  TYPE_1__ cdf_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDF_UNPACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDF_UNPACKA (int /*<<< orphan*/ ) ; 
 size_t __arraycount (int /*<<< orphan*/ *) ; 

void
cdf_unpack_header(cdf_header_t *h, char *buf)
{
	size_t i;
	size_t len = 0;

	CDF_UNPACK(h->h_magic);
	CDF_UNPACKA(h->h_uuid);
	CDF_UNPACK(h->h_revision);
	CDF_UNPACK(h->h_version);
	CDF_UNPACK(h->h_byte_order);
	CDF_UNPACK(h->h_sec_size_p2);
	CDF_UNPACK(h->h_short_sec_size_p2);
	CDF_UNPACKA(h->h_unused0);
	CDF_UNPACK(h->h_num_sectors_in_sat);
	CDF_UNPACK(h->h_secid_first_directory);
	CDF_UNPACKA(h->h_unused1);
	CDF_UNPACK(h->h_min_size_standard_stream);
	CDF_UNPACK(h->h_secid_first_sector_in_short_sat);
	CDF_UNPACK(h->h_num_sectors_in_short_sat);
	CDF_UNPACK(h->h_secid_first_sector_in_master_sat);
	CDF_UNPACK(h->h_num_sectors_in_master_sat);
	for (i = 0; i < __arraycount(h->h_master_sat); i++)
		CDF_UNPACK(h->h_master_sat[i]);
}