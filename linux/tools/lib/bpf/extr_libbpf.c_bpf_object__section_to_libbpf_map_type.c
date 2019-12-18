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
struct TYPE_2__ {int data_shndx; int bss_shndx; int rodata_shndx; } ;
struct bpf_object {TYPE_1__ efile; } ;
typedef  enum libbpf_map_type { ____Placeholder_libbpf_map_type } libbpf_map_type ;

/* Variables and functions */
 int LIBBPF_MAP_BSS ; 
 int LIBBPF_MAP_DATA ; 
 int LIBBPF_MAP_RODATA ; 
 int LIBBPF_MAP_UNSPEC ; 

__attribute__((used)) static enum libbpf_map_type
bpf_object__section_to_libbpf_map_type(const struct bpf_object *obj, int shndx)
{
	if (shndx == obj->efile.data_shndx)
		return LIBBPF_MAP_DATA;
	else if (shndx == obj->efile.bss_shndx)
		return LIBBPF_MAP_BSS;
	else if (shndx == obj->efile.rodata_shndx)
		return LIBBPF_MAP_RODATA;
	else
		return LIBBPF_MAP_UNSPEC;
}