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
struct annotation_line {void* privsize; int /*<<< orphan*/  line; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_srcline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void annotation_line__delete(struct annotation_line *al)
{
	void *ptr = (void *) al - al->privsize;

	free_srcline(al->path);
	zfree(&al->line);
	free(ptr);
}