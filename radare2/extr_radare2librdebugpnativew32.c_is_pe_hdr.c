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
struct TYPE_4__ {scalar_t__ e_magic; int e_lfanew; } ;
struct TYPE_3__ {scalar_t__ Signature; } ;
typedef  TYPE_1__ IMAGE_NT_HEADERS ;
typedef  TYPE_2__ IMAGE_DOS_HEADER ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_SIGNATURE ; 
 scalar_t__ IMAGE_NT_SIGNATURE ; 

__attribute__((used)) static inline int is_pe_hdr(unsigned char *pe_hdr) {
	IMAGE_DOS_HEADER *dos_header = (IMAGE_DOS_HEADER *)pe_hdr;
	IMAGE_NT_HEADERS *nt_headers;

	if (dos_header->e_magic==IMAGE_DOS_SIGNATURE) {
		nt_headers = (IMAGE_NT_HEADERS *)((char *)dos_header
				+ dos_header->e_lfanew);
		if (nt_headers->Signature==IMAGE_NT_SIGNATURE)
			return 1;
	}
	return 0;
}