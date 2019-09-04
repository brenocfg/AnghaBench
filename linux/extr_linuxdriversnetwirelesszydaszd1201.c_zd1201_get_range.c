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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_2__ {int qual; int level; int noise; int updated; } ;
struct iw_range {int* encoding_size; int num_encoding_sizes; int num_bitrates; int* bitrate; int /*<<< orphan*/  min_frag; int /*<<< orphan*/  max_rts; scalar_t__ min_rts; int /*<<< orphan*/  max_encoding_tokens; TYPE_1__ max_qual; void* we_version_source; void* we_version_compiled; } ;
struct iw_point {int length; } ;

/* Variables and functions */
 void* WIRELESS_EXT ; 
 int /*<<< orphan*/  ZD1201_FRAGMAX ; 
 int /*<<< orphan*/  ZD1201_FRAGMIN ; 
 int /*<<< orphan*/  ZD1201_NUMKEYS ; 
 int /*<<< orphan*/  ZD1201_RTSMAX ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zd1201_get_range(struct net_device *dev,
    struct iw_request_info *info, struct iw_point *wrq, char *extra)
{
	struct iw_range *range = (struct iw_range *)extra;

	wrq->length = sizeof(struct iw_range);
	memset(range, 0, sizeof(struct iw_range));
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = WIRELESS_EXT;

	range->max_qual.qual = 128;
	range->max_qual.level = 128;
	range->max_qual.noise = 128;
	range->max_qual.updated = 7;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = ZD1201_NUMKEYS;

	range->num_bitrates = 4;
	range->bitrate[0] = 1000000;
	range->bitrate[1] = 2000000;
	range->bitrate[2] = 5500000;
	range->bitrate[3] = 11000000;

	range->min_rts = 0;
	range->min_frag = ZD1201_FRAGMIN;
	range->max_rts = ZD1201_RTSMAX;
	range->min_frag = ZD1201_FRAGMAX;

	return 0;
}