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
struct btf_ext {void const* data; int /*<<< orphan*/  data_size; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

const void *btf_ext__get_raw_data(const struct btf_ext *btf_ext, __u32 *size)
{
	*size = btf_ext->data_size;
	return btf_ext->data;
}