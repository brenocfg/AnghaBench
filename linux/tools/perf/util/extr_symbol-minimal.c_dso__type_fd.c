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
typedef  enum dso_type { ____Placeholder_dso_type } dso_type ;
typedef  int /*<<< orphan*/  ehdr ;
struct TYPE_3__ {scalar_t__ e_machine; } ;
typedef  TYPE_1__ Elf64_Ehdr ;

/* Variables and functions */
 int DSO__TYPE_32BIT ; 
 int DSO__TYPE_64BIT ; 
 int DSO__TYPE_UNKNOWN ; 
 int DSO__TYPE_X32BIT ; 
 scalar_t__ EM_X86_64 ; 
 int fd__is_64_bit (int) ; 
 int readn (int,TYPE_1__*,int) ; 

enum dso_type dso__type_fd(int fd)
{
	Elf64_Ehdr ehdr;
	int ret;

	ret = fd__is_64_bit(fd);
	if (ret < 0)
		return DSO__TYPE_UNKNOWN;

	if (ret)
		return DSO__TYPE_64BIT;

	if (readn(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr))
		return DSO__TYPE_UNKNOWN;

	if (ehdr.e_machine == EM_X86_64)
		return DSO__TYPE_X32BIT;

	return DSO__TYPE_32BIT;
}