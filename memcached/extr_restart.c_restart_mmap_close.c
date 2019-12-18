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
 int /*<<< orphan*/  MS_SYNC ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_file ; 
 int /*<<< orphan*/  mmap_base ; 
 int /*<<< orphan*/  mmap_fd ; 
 int /*<<< orphan*/  msync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ restart_save (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabmem_limit ; 
 int /*<<< orphan*/  stderr ; 

void restart_mmap_close(void) {
    msync(mmap_base, slabmem_limit, MS_SYNC);

    if (restart_save(memory_file) != 0) {
        fprintf(stderr, "[restart] failed to save metadata");
    }

    if (munmap(mmap_base, slabmem_limit) != 0) {
        perror("[restart] failed to munmap shared memory");
    } else if (close(mmap_fd) != 0) {
        perror("[restart] failed to close shared memory fd");
    }

    free(memory_file);
}