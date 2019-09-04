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
struct TYPE_4__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
delta_coder_end(lzma_coder *coder, lzma_allocator *allocator)
{
	lzma_next_end(&coder->next, allocator);
	lzma_free(coder, allocator);
	return;
}