#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stream {int dummy; } ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ rar_block_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 scalar_t__ IgnoreBlock (struct stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAR_BLOCK_ARCHIVE ; 
 int RAR_BLOCK_END_HAS_NEXT ; 
 int /*<<< orphan*/  RAR_BLOCK_MARKER ; 
 scalar_t__ SkipBlock (struct stream*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rar_marker ; 
 scalar_t__ rar_marker_size ; 
 TYPE_2__ stream_peek (struct stream*,scalar_t__) ; 
 int /*<<< orphan*/  stream_skip (struct stream*,int) ; 

__attribute__((used)) static int SkipEnd(struct stream *s, const rar_block_t *hdr)
{
    if (!(hdr->flags & RAR_BLOCK_END_HAS_NEXT))
        return -1;

    if (SkipBlock(s, hdr))
        return -1;

    /* Now, we need to look for a marker block,
     * It seems that there is garbage at EOF */
    for (;;) {
        bstr peek = stream_peek(s, rar_marker_size);

        if (peek.len < rar_marker_size)
            return -1;

        if (!memcmp(peek.start, rar_marker, rar_marker_size))
            break;

        if (!stream_skip(s, 1))
            return -1;
    }

    /* Skip marker and archive blocks */
    if (IgnoreBlock(s, RAR_BLOCK_MARKER))
        return -1;
    if (IgnoreBlock(s, RAR_BLOCK_ARCHIVE))
        return -1;

    return 0;
}