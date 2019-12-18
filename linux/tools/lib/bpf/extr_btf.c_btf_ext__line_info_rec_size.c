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
struct TYPE_2__ {int /*<<< orphan*/  rec_size; } ;
struct btf_ext {TYPE_1__ line_info; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__u32 btf_ext__line_info_rec_size(const struct btf_ext *btf_ext)
{
	return btf_ext->line_info.rec_size;
}