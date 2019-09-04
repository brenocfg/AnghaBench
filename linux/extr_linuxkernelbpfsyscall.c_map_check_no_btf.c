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
struct btf_type {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

int map_check_no_btf(const struct bpf_map *map,
		     const struct btf_type *key_type,
		     const struct btf_type *value_type)
{
	return -ENOTSUPP;
}