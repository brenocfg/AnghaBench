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
struct audit_chunk {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_chunk (struct audit_chunk*) ; 

void audit_put_chunk(struct audit_chunk *chunk)
{
	if (atomic_long_dec_and_test(&chunk->refs))
		free_chunk(chunk);
}