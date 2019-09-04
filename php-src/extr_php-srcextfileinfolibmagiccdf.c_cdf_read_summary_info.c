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
typedef  int /*<<< orphan*/  cdf_stream_t ;
typedef  int /*<<< orphan*/  cdf_sat_t ;
typedef  int /*<<< orphan*/  cdf_info_t ;
typedef  int /*<<< orphan*/  cdf_header_t ;
typedef  int /*<<< orphan*/  cdf_dir_t ;

/* Variables and functions */
 int cdf_read_user_stream (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 

int
cdf_read_summary_info(const cdf_info_t *info, const cdf_header_t *h,
    const cdf_sat_t *sat, const cdf_sat_t *ssat, const cdf_stream_t *sst,
    const cdf_dir_t *dir, cdf_stream_t *scn)
{
	return cdf_read_user_stream(info, h, sat, ssat, sst, dir,
	    "\05SummaryInformation", scn);
}