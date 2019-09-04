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
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  cl_cached_program_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* read_file (char const*,int /*<<< orphan*/ *) ; 

cl_program cl_cached_program_from_file(cl_context ctx, cl_device_id device_id, const char* path, const char* args,
                                       uint64_t *out_hash) {
  char* src_buf = read_file(path, NULL);
  assert(src_buf);
  cl_program ret = cl_cached_program_from_string(ctx, device_id, src_buf, args, out_hash);
  free(src_buf);
  return ret;
}