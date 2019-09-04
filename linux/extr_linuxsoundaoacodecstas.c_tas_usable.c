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
struct transfer_info {int dummy; } ;
struct codec_info_item {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int tas_usable(struct codec_info_item *cii,
		      struct transfer_info *ti,
		      struct transfer_info *out)
{
	return 1;
}