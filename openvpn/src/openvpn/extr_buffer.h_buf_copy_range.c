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
struct buffer {int len; scalar_t__ offset; scalar_t__ capacity; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static inline bool
buf_copy_range(struct buffer *dest,
               int dest_index,
               const struct buffer *src,
               int src_index,
               int src_len)
{
    if (src_index < 0
        || src_len < 0
        || src_index + src_len > src->len
        || dest_index < 0
        || dest->offset + dest_index + src_len > dest->capacity)
    {
        return false;
    }
    memcpy(dest->data + dest->offset + dest_index, src->data + src->offset + src_index, src_len);
    if (dest_index + src_len > dest->len)
    {
        dest->len = dest_index + src_len;
    }
    return true;
}