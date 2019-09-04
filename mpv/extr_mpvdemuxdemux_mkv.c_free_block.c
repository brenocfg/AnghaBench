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
struct block_info {int num_laces; int /*<<< orphan*/  additions; int /*<<< orphan*/ * laces; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_block(struct block_info *block)
{
    for (int n = 0; n < block->num_laces; n++)
        av_buffer_unref(&block->laces[n]);
    block->num_laces = 0;
    TA_FREEP(&block->additions);
}