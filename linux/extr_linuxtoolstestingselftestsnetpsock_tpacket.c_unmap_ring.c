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
struct ring {int /*<<< orphan*/  rd; int /*<<< orphan*/  mm_len; int /*<<< orphan*/  mm_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_ring(int sock, struct ring *ring)
{
	munmap(ring->mm_space, ring->mm_len);
	free(ring->rd);
}