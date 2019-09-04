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
struct block_info {int dummy; } ;
typedef  int /*<<< orphan*/  demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_block (struct block_info*) ; 
 int handle_block (int /*<<< orphan*/ *,struct block_info*) ; 
 int read_next_block (int /*<<< orphan*/ *,struct block_info*) ; 

__attribute__((used)) static int demux_mkv_fill_buffer(demuxer_t *demuxer)
{
    for (;;) {
        int res;
        struct block_info block;
        res = read_next_block(demuxer, &block);
        if (res < 0)
            return 0;
        if (res > 0) {
            res = handle_block(demuxer, &block);
            free_block(&block);
            if (res > 0)
                return 1;
        }
    }
}