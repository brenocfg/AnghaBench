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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int const,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t const,size_t) ; 
 size_t fwrite (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 

__attribute__((used)) static char* fuzzer_get_tmpfile(const uint8_t* data, size_t size) {
  char* filename_buffer = strdup("/tmp/generate_temporary_file.XXXXXX");
  if (!filename_buffer) {
    perror("Failed to allocate file name buffer.");
    abort();
  }
  const int file_descriptor = mkstemp(filename_buffer);
  if (file_descriptor < 0) {
    perror("Failed to make temporary file.");
    abort();
  }
  FILE* file = fdopen(file_descriptor, "wb");
  if (!file) {
    perror("Failed to open file descriptor.");
    close(file_descriptor);
    abort();
  }
  const size_t bytes_written = fwrite(data, sizeof(uint8_t), size, file);
  if (bytes_written < size) {
    close(file_descriptor);
    fprintf(stderr, "Failed to write all bytes to file (%zu out of %zu)",
            bytes_written, size);
    abort();
  }
  fclose(file);
  return filename_buffer;
}