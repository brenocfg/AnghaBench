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
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * buf_read_alloc (struct buffer*,int) ; 
 int buf_write (struct buffer*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline bool
buf_copy_n(struct buffer *dest, struct buffer *src, int n)
{
    uint8_t *cp = buf_read_alloc(src, n);
    if (!cp)
    {
        return false;
    }
    return buf_write(dest, cp, n);
}