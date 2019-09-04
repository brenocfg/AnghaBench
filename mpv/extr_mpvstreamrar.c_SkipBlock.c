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
typedef  scalar_t__ uint64_t ;
struct stream {int dummy; } ;
struct TYPE_3__ {scalar_t__ add_size; scalar_t__ size; } ;
typedef  TYPE_1__ rar_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int MPMIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_skip (struct stream*,int) ; 

__attribute__((used)) static int SkipBlock(struct stream *s, const rar_block_t *hdr)
{
    uint64_t size = (uint64_t)hdr->size + hdr->add_size;

    while (size > 0) {
        int skip = MPMIN(size, INT_MAX);
        if (!stream_skip(s, skip))
            return -1;

        size -= skip;
    }
    return 0;
}