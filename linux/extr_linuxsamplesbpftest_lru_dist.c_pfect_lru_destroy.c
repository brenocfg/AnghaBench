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
struct pfect_lru {int /*<<< orphan*/  free_nodes; int /*<<< orphan*/  map_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pfect_lru_destroy(struct pfect_lru *lru)
{
	close(lru->map_fd);
	free(lru->free_nodes);
}