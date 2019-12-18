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
typedef  int /*<<< orphan*/  mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  MPG123_ADD_FLAGS ; 
 int MPG123_OK ; 
 int /*<<< orphan*/  MPG123_QUIET ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 char* fuzzer_get_tmpfile (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  fuzzer_release_tmpfile (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  mpg123_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpg123_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpg123_init () ; 
 int /*<<< orphan*/ * mpg123_new (int /*<<< orphan*/ *,int*) ; 
 int mpg123_open (int /*<<< orphan*/ *,char*) ; 
 int mpg123_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mpg123_read (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*) ; 
 int mpg123_tell_stream (int /*<<< orphan*/ *) ; 
 int mpg123_tellframe (int /*<<< orphan*/ *) ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    mpg123_init();
    initialized = true;
  }
  char* filename = fuzzer_get_tmpfile(data, size);
  if (filename == NULL) {
    return 0;
  }

  size_t outmemorysize = size * 2;  // Guess based on the size of data.
  unsigned char* outmemory = (unsigned char*)malloc(outmemorysize);
  if (outmemory == NULL) {
    fuzzer_release_tmpfile(filename);
    return 0;
  }

  int error;
  mpg123_handle* handle = mpg123_new(NULL, &error);
  if (handle == NULL || mpg123_param(handle,
      MPG123_ADD_FLAGS, MPG123_QUIET, 0.) != MPG123_OK) {
    free(outmemory);
    fuzzer_release_tmpfile(filename);
    return 0;
  }

  if (mpg123_open(handle, filename) == MPG123_OK) {
    int read_error;
    do {
      size_t decoded_size;
      read_error = mpg123_read(handle, outmemory, outmemorysize, &decoded_size);
    } while (read_error == MPG123_OK && mpg123_tellframe(handle) <= 10000
          && mpg123_tell_stream(handle) <= 1<<20);
  }

  mpg123_close(handle);
  mpg123_delete(handle);
  free(outmemory);
  fuzzer_release_tmpfile(filename);
  return 0;
}