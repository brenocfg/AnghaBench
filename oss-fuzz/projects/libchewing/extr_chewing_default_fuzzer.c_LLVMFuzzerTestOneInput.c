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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stress_argv ;

/* Variables and functions */
 int /*<<< orphan*/  const* fuzz_input ; 
 int /*<<< orphan*/  const* fuzz_ptr ; 
 size_t fuzz_size ; 
 int /*<<< orphan*/  stress_main (int,char**) ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  fuzz_input = fuzz_ptr = data;
  fuzz_size = size;

  const char* stress_argv[] = {
      "./chewing_fuzzer", "-loop", "1", NULL,
  };
  stress_main(sizeof(stress_argv) / sizeof(stress_argv[0]) - 1,
              (char**)stress_argv);
  return 0;
}