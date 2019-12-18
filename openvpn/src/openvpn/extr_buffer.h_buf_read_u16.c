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
typedef  int /*<<< orphan*/  uint16_t ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_read (struct buffer*,int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
buf_read_u16(struct buffer *buf)
{
    uint16_t ret;
    if (!buf_read(buf, &ret, sizeof(uint16_t)))
    {
        return -1;
    }
    return ntohs(ret);
}