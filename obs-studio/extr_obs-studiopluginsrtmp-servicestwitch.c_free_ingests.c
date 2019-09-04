#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ingest {int /*<<< orphan*/  url; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {size_t num; struct ingest* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ cur_ingests ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

__attribute__((used)) static void free_ingests(void)
{
	for (size_t i = 0; i < cur_ingests.num; i++) {
		struct ingest *ingest = cur_ingests.array + i;
		bfree(ingest->name);
		bfree(ingest->url);
	}

	da_free(cur_ingests);
}