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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u64 ;
struct perf_header {int needs_swap; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  magic ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_HEADER_VERSION_1 ; 
 int /*<<< orphan*/  PERF_HEADER_VERSION_2 ; 
 int /*<<< orphan*/  __perf_magic1 ; 
 scalar_t__ __perf_magic2 ; 
 scalar_t__ __perf_magic2_sw ; 
 int memcmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int try_all_file_abis (int /*<<< orphan*/ ,struct perf_header*) ; 
 int try_all_pipe_abis (int /*<<< orphan*/ ,struct perf_header*) ; 

__attribute__((used)) static int check_magic_endian(u64 magic, uint64_t hdr_sz,
			      bool is_pipe, struct perf_header *ph)
{
	int ret;

	/* check for legacy format */
	ret = memcmp(&magic, __perf_magic1, sizeof(magic));
	if (ret == 0) {
		ph->version = PERF_HEADER_VERSION_1;
		pr_debug("legacy perf.data format\n");
		if (is_pipe)
			return try_all_pipe_abis(hdr_sz, ph);

		return try_all_file_abis(hdr_sz, ph);
	}
	/*
	 * the new magic number serves two purposes:
	 * - unique number to identify actual perf.data files
	 * - encode endianness of file
	 */
	ph->version = PERF_HEADER_VERSION_2;

	/* check magic number with one endianness */
	if (magic == __perf_magic2)
		return 0;

	/* check magic number with opposite endianness */
	if (magic != __perf_magic2_sw)
		return -1;

	ph->needs_swap = true;

	return 0;
}