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
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_advance (struct buffer*,int) ; 

__attribute__((used)) static inline void
link_socket_write_post_size_adjust(int *size,
                                   int size_delta,
                                   struct buffer *buf)
{
    if (size_delta > 0 && *size > size_delta)
    {
        *size -= size_delta;
        if (!buf_advance(buf, size_delta))
        {
            *size = 0;
        }
    }
}