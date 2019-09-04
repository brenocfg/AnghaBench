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
struct TYPE_3__ {int* e_ident; } ;
struct TYPE_4__ {TYPE_1__ ehdr; } ;
struct bpf_object {TYPE_2__ efile; } ;

/* Variables and functions */
 size_t EI_DATA ; 
#define  ELFDATA2LSB 129 
#define  ELFDATA2MSB 128 
 int LIBBPF_ERRNO__ENDIAN ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static int
bpf_object__check_endianness(struct bpf_object *obj)
{
	static unsigned int const endian = 1;

	switch (obj->efile.ehdr.e_ident[EI_DATA]) {
	case ELFDATA2LSB:
		/* We are big endian, BPF obj is little endian. */
		if (*(unsigned char const *)&endian != 1)
			goto mismatch;
		break;

	case ELFDATA2MSB:
		/* We are little endian, BPF obj is big endian. */
		if (*(unsigned char const *)&endian != 0)
			goto mismatch;
		break;
	default:
		return -LIBBPF_ERRNO__ENDIAN;
	}

	return 0;

mismatch:
	pr_warning("Error: endianness mismatch.\n");
	return -LIBBPF_ERRNO__ENDIAN;
}