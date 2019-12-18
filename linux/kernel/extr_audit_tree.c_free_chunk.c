#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct audit_chunk {int count; TYPE_1__* owners; } ;
struct TYPE_2__ {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct audit_chunk*) ; 
 int /*<<< orphan*/  put_tree (scalar_t__) ; 

__attribute__((used)) static void free_chunk(struct audit_chunk *chunk)
{
	int i;

	for (i = 0; i < chunk->count; i++) {
		if (chunk->owners[i].owner)
			put_tree(chunk->owners[i].owner);
	}
	kfree(chunk);
}