#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFDATA2MSB ; 

__attribute__((used)) static bool btf_check_endianness(const GElf_Ehdr *ehdr)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	return ehdr->e_ident[EI_DATA] == ELFDATA2LSB;
#elif __BYTE_ORDER == __BIG_ENDIAN
	return ehdr->e_ident[EI_DATA] == ELFDATA2MSB;
#else
# error "Unrecognized __BYTE_ORDER__"
#endif
}