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
typedef  int /*<<< orphan*/  uint8_t ;
struct buffer {int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_assign (struct buffer*,struct buffer*) ; 

__attribute__((used)) static inline void
buffer_turnover(const uint8_t *orig_buf, struct buffer *dest_stub, struct buffer *src_stub, struct buffer *storage)
{
    if (orig_buf == src_stub->data && src_stub->data != storage->data)
    {
        buf_assign(storage, src_stub);
        *dest_stub = *storage;
    }
    else
    {
        *dest_stub = *src_stub;
    }
}