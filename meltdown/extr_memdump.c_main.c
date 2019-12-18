#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int retries; int measurements; void* physical_offset; } ;
typedef  TYPE_1__ libkdump_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libkdump_cleanup () ; 
 TYPE_1__ libkdump_get_autoconfig () ; 
 int /*<<< orphan*/  libkdump_init (TYPE_1__) ; 
 size_t libkdump_phys_to_virt (size_t) ; 
 int libkdump_read (size_t) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  sigint ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
  size_t phys = 1ull * 1024ull * 1024ull * 1024ull; // start at first gigabyte
  size_t size = (size_t)-1ULL;
  if (argc >= 2) {
    phys = strtoull(argv[1], NULL, 0);
  }
  if (argc >= 3) {
    size = strtoull(argv[2], NULL, 0);
  }

  int width = 16; // characters per line
  int suppress_empty = 1;

  libkdump_config_t config;
  config = libkdump_get_autoconfig();
  config.retries = 10;
  config.measurements = 2;
  if (argc >= 4) {
    config.physical_offset = strtoull(argv[3], NULL, 0);
  }

  libkdump_init(config);

  size_t vaddr = libkdump_phys_to_virt(phys);

  if (vaddr == -1ULL) {
    fprintf(stderr, "Error converting physical to virtual address\n");
    return -1;
  }

  printf(
      "\x1b[32;1m[+]\x1b[0m Physical address       : \x1b[33;1m0x%zx\x1b[0m\n", phys);
  printf("\x1b[32;1m[+]\x1b[0m Physical offset        : \x1b[33;1m0x%zx\x1b[0m\n", config.physical_offset);
  printf(
      "\x1b[32;1m[+]\x1b[0m Virtual address       : \x1b[33;1m0x%zx\x1b[0m\n", vaddr);

  if (width > size)
     width = size;

  size_t delta = 0;
  int i;
  char *buffer = malloc(width);

  signal(SIGINT, sigint);

  while (running && delta < size) {
    int value = libkdump_read(vaddr + delta);
    buffer[delta % width] = value;

    if (delta % width == width - 1) {
      int skip = 1;
      for (i = 0; i < width; i++) {
        if (buffer[i]) {
          skip = 0;
          break;
        }
      }
      if (skip && suppress_empty) {
        delta++;
        continue;
      }

      printf("%10zx: ", delta + phys - (width - 1));
      printf("| ");
      for (i = 0; i < width; i++) {
        printf("%02x ", (unsigned char)buffer[i]);
      }
      printf("| ");
      for (i = 0; i < width; i++) {
        printf("%c", (buffer[i] >= 32 && buffer[i] <= 126) ? buffer[i] : '.');
      }
      printf(" |\n");
    }
    delta++;
  }

  free(buffer);
  libkdump_cleanup();

  return 0;
}