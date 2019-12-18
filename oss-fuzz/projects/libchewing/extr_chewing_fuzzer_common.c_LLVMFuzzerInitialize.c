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
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mktemp (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 char* userphrase_path ; 

int LLVMFuzzerInitialize(int* argc, char*** argv) {
  char* exe_path = (*argv)[0];

  // dirname() can modify its argument.
  char* exe_path_copy = strdup(exe_path);
  char* dir = dirname(exe_path_copy);

  // Assume data files are at the same location as executable.
  setenv("CHEWING_PATH", dir, 0);
  free(exe_path_copy);

  // Specify user db of this process. So we can run multiple fuzzers at the
  // same time.
  mktemp(userphrase_path);
  setenv("TEST_USERPHRASE_PATH", userphrase_path, 0);
  return 0;
}