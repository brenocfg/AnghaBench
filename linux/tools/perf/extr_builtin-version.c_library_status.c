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

/* Variables and functions */
 int /*<<< orphan*/  HAVE_AIO_SUPPORT ; 
 int /*<<< orphan*/  HAVE_AUXTRACE_SUPPORT ; 
 int /*<<< orphan*/  HAVE_DWARF_GETLOCATIONS_SUPPORT ; 
 int /*<<< orphan*/  HAVE_DWARF_SUPPORT ; 
 int /*<<< orphan*/  HAVE_GLIBC_SUPPORT ; 
 int /*<<< orphan*/  HAVE_GTK2_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBAUDIT_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBBFD_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBBPF_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBCRYPTO_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBELF_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBNUMA_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBPERL_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBPYTHON_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LIBUNWIND_SUPPORT ; 
 int /*<<< orphan*/  HAVE_LZMA_SUPPORT ; 
 int /*<<< orphan*/  HAVE_SLANG_SUPPORT ; 
 int /*<<< orphan*/  HAVE_SYSCALL_TABLE_SUPPORT ; 
 int /*<<< orphan*/  HAVE_ZLIB_SUPPORT ; 
 int /*<<< orphan*/  HAVE_ZSTD_SUPPORT ; 
 int /*<<< orphan*/  STATUS (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ aio ; 
 scalar_t__ bpf ; 
 scalar_t__ dwarf ; 
 scalar_t__ dwarf_getlocations ; 
 scalar_t__ get_cpuid ; 
 scalar_t__ glibc ; 
 scalar_t__ gtk2 ; 
 scalar_t__ libaudit ; 
 scalar_t__ libbfd ; 
 scalar_t__ libcrypto ; 
 scalar_t__ libdw ; 
 scalar_t__ libelf ; 
 scalar_t__ libnuma ; 
 scalar_t__ libperl ; 
 scalar_t__ libpython ; 
 scalar_t__ libslang ; 
 scalar_t__ libunwind ; 
 scalar_t__ lzma ; 
 scalar_t__ numa_num_possible_cpus ; 
 scalar_t__ syscall_table ; 
 scalar_t__ unwind ; 
 scalar_t__ zlib ; 
 scalar_t__ zstd ; 

__attribute__((used)) static void library_status(void)
{
	STATUS(HAVE_DWARF_SUPPORT, dwarf);
	STATUS(HAVE_DWARF_GETLOCATIONS_SUPPORT, dwarf_getlocations);
	STATUS(HAVE_GLIBC_SUPPORT, glibc);
	STATUS(HAVE_GTK2_SUPPORT, gtk2);
#ifndef HAVE_SYSCALL_TABLE_SUPPORT
	STATUS(HAVE_LIBAUDIT_SUPPORT, libaudit);
#endif
	STATUS(HAVE_SYSCALL_TABLE_SUPPORT, syscall_table);
	STATUS(HAVE_LIBBFD_SUPPORT, libbfd);
	STATUS(HAVE_LIBELF_SUPPORT, libelf);
	STATUS(HAVE_LIBNUMA_SUPPORT, libnuma);
	STATUS(HAVE_LIBNUMA_SUPPORT, numa_num_possible_cpus);
	STATUS(HAVE_LIBPERL_SUPPORT, libperl);
	STATUS(HAVE_LIBPYTHON_SUPPORT, libpython);
	STATUS(HAVE_SLANG_SUPPORT, libslang);
	STATUS(HAVE_LIBCRYPTO_SUPPORT, libcrypto);
	STATUS(HAVE_LIBUNWIND_SUPPORT, libunwind);
	STATUS(HAVE_DWARF_SUPPORT, libdw-dwarf-unwind);
	STATUS(HAVE_ZLIB_SUPPORT, zlib);
	STATUS(HAVE_LZMA_SUPPORT, lzma);
	STATUS(HAVE_AUXTRACE_SUPPORT, get_cpuid);
	STATUS(HAVE_LIBBPF_SUPPORT, bpf);
	STATUS(HAVE_AIO_SUPPORT, aio);
	STATUS(HAVE_ZSTD_SUPPORT, zstd);
}