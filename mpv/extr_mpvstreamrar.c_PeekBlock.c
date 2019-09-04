#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct stream {int dummy; } ;
struct TYPE_5__ {int flags; int size; int /*<<< orphan*/  add_size; int /*<<< orphan*/  type; void* crc; } ;
typedef  TYPE_1__ rar_block_t ;
struct TYPE_6__ {int len; scalar_t__ start; } ;
typedef  TYPE_2__ bstr ;

/* Variables and functions */
 void* AV_RL16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RAR_BLOCK_FILE ; 
 int /*<<< orphan*/  RAR_BLOCK_SUBBLOCK ; 
 TYPE_2__ stream_peek (struct stream*,int) ; 

__attribute__((used)) static int PeekBlock(struct stream *s, rar_block_t *hdr)
{
    bstr data = stream_peek(s, 11);
    const uint8_t *peek = (uint8_t *)data.start;
    int peek_size = data.len;

    if (peek_size < 7)
        return -1;

    hdr->crc   = AV_RL16(&peek[0]);
    hdr->type  = peek[2];
    hdr->flags = AV_RL16(&peek[3]);
    hdr->size  = AV_RL16(&peek[5]);
    hdr->add_size = 0;
    if ((hdr->flags & 0x8000) ||
        hdr->type == RAR_BLOCK_FILE ||
        hdr->type == RAR_BLOCK_SUBBLOCK) {
        if (peek_size < 11)
            return -1;
        hdr->add_size = AV_RL32(&peek[7]);
    }

    if (hdr->size < 7)
        return -1;
    return 0;
}