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
typedef  int /*<<< orphan*/  cl_program ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_cached_program_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 

cl_program cl_index_program_from_string(cl_context ctx, cl_device_id device_id,
                                        const char* src, const char* args,
                                        uint64_t index_hash) {
  uint64_t src_hash = 0;
  cl_program ret = cl_cached_program_from_string(ctx, device_id, src, args, &src_hash);
#ifndef CLU_NO_CACHE
  add_index(index_hash, src_hash);
#endif
  return ret;
}