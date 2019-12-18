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
 int /*<<< orphan*/  main_test_backtrace () ; 
 int /*<<< orphan*/  main_test_bpf () ; 
 int /*<<< orphan*/  main_test_disassembler_four_args () ; 
 int /*<<< orphan*/  main_test_dwarf () ; 
 int /*<<< orphan*/  main_test_dwarf_getlocations () ; 
 int /*<<< orphan*/  main_test_eventfd () ; 
 int /*<<< orphan*/  main_test_get_cpuid () ; 
 int /*<<< orphan*/  main_test_get_current_dir_name () ; 
 int /*<<< orphan*/  main_test_gettid () ; 
 int /*<<< orphan*/  main_test_glibc () ; 
 int /*<<< orphan*/  main_test_gtk2 (int,char**) ; 
 int /*<<< orphan*/  main_test_gtk2_infobar (int,char**) ; 
 int /*<<< orphan*/  main_test_hello () ; 
 int /*<<< orphan*/  main_test_libaio () ; 
 int /*<<< orphan*/  main_test_libaudit () ; 
 int /*<<< orphan*/  main_test_libbfd () ; 
 int /*<<< orphan*/  main_test_libcrypto () ; 
 int /*<<< orphan*/  main_test_libdw_dwarf_unwind () ; 
 int /*<<< orphan*/  main_test_libelf () ; 
 int /*<<< orphan*/  main_test_libelf_gelf_getnote () ; 
 int /*<<< orphan*/  main_test_libelf_getphdrnum () ; 
 int /*<<< orphan*/  main_test_libelf_getshdrstrndx () ; 
 int /*<<< orphan*/  main_test_libelf_mmap () ; 
 int /*<<< orphan*/  main_test_libnuma () ; 
 int /*<<< orphan*/  main_test_libperl () ; 
 int /*<<< orphan*/  main_test_libpython () ; 
 int /*<<< orphan*/  main_test_libpython_version () ; 
 int /*<<< orphan*/  main_test_libslang () ; 
 int /*<<< orphan*/  main_test_libunwind () ; 
 int /*<<< orphan*/  main_test_libzstd () ; 
 int /*<<< orphan*/  main_test_lzma () ; 
 int /*<<< orphan*/  main_test_numa_num_possible_cpus () ; 
 int /*<<< orphan*/  main_test_pthread_attr_setaffinity_np () ; 
 int /*<<< orphan*/  main_test_pthread_barrier () ; 
 int /*<<< orphan*/  main_test_reallocarray () ; 
 int /*<<< orphan*/  main_test_sched_getcpu () ; 
 int /*<<< orphan*/  main_test_sdt () ; 
 int /*<<< orphan*/  main_test_setns () ; 
 int /*<<< orphan*/  main_test_stackprotector_all () ; 
 int /*<<< orphan*/  main_test_sync_compare_and_swap (int,char**) ; 
 int /*<<< orphan*/  main_test_timerfd () ; 
 int /*<<< orphan*/  main_test_zlib () ; 

int main(int argc, char *argv[])
{
	main_test_libpython();
	main_test_libpython_version();
	main_test_libperl();
	main_test_hello();
	main_test_libelf();
	main_test_libelf_mmap();
	main_test_get_current_dir_name();
	main_test_gettid();
	main_test_glibc();
	main_test_dwarf();
	main_test_dwarf_getlocations();
	main_test_eventfd();
	main_test_libelf_getphdrnum();
	main_test_libelf_gelf_getnote();
	main_test_libelf_getshdrstrndx();
	main_test_libunwind();
	main_test_libaudit();
	main_test_libslang();
	main_test_gtk2(argc, argv);
	main_test_gtk2_infobar(argc, argv);
	main_test_libbfd();
	main_test_backtrace();
	main_test_libnuma();
	main_test_numa_num_possible_cpus();
	main_test_timerfd();
	main_test_stackprotector_all();
	main_test_libdw_dwarf_unwind();
	main_test_sync_compare_and_swap(argc, argv);
	main_test_zlib();
	main_test_pthread_attr_setaffinity_np();
	main_test_pthread_barrier();
	main_test_lzma();
	main_test_get_cpuid();
	main_test_bpf();
	main_test_libcrypto();
	main_test_sched_getcpu();
	main_test_sdt();
	main_test_setns();
	main_test_libaio();
	main_test_reallocarray();
	main_test_disassembler_four_args();
	main_test_libzstd();

	return 0;
}