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
 int /*<<< orphan*/  buf_write_u16 (struct buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
write_empty_string(struct buffer *buf)
{
    if (!buf_write_u16(buf, 0))
    {
        return false;
    }
    return true;
}