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
typedef  int /*<<< orphan*/  uint32_t ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_read (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
buf_read_u32(struct buffer *buf, bool *good)
{
    uint32_t ret;
    if (!buf_read(buf, &ret, sizeof(uint32_t)))
    {
        if (good)
        {
            *good = false;
        }
        return 0;
    }
    else
    {
        if (good)
        {
            *good = true;
        }
        return ntohl(ret);
    }
}