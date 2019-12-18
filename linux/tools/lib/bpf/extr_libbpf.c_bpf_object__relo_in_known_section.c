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
struct TYPE_2__ {int text_shndx; } ;
struct bpf_object {TYPE_1__ efile; } ;

/* Variables and functions */
 scalar_t__ bpf_object__shndx_is_data (struct bpf_object const*,int) ; 
 scalar_t__ bpf_object__shndx_is_maps (struct bpf_object const*,int) ; 

__attribute__((used)) static bool bpf_object__relo_in_known_section(const struct bpf_object *obj,
					      int shndx)
{
	return shndx == obj->efile.text_shndx ||
	       bpf_object__shndx_is_maps(obj, shndx) ||
	       bpf_object__shndx_is_data(obj, shndx);
}