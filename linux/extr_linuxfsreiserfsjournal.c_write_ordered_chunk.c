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
struct buffer_chunk {int nr; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  submit_ordered_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_ordered_chunk(struct buffer_chunk *chunk)
{
	int i;
	for (i = 0; i < chunk->nr; i++) {
		submit_ordered_buffer(chunk->bh[i]);
	}
	chunk->nr = 0;
}