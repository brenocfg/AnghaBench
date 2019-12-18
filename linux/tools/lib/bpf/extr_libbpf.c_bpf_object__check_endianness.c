#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* e_ident; } ;
struct TYPE_4__ {TYPE_1__ ehdr; } ;
struct bpf_object {TYPE_2__ efile; } ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFDATA2MSB ; 
 int LIBBPF_ERRNO__ENDIAN ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int bpf_object__check_endianness(struct bpf_object *obj)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	if (obj->efile.ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		return 0;
#elif __BYTE_ORDER == __BIG_ENDIAN
	if (obj->efile.ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
		return 0;
#else
# error "Unrecognized __BYTE_ORDER__"
#endif
	pr_warning("endianness mismatch.\n");
	return -LIBBPF_ERRNO__ENDIAN;
}