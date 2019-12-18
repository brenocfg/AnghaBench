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
 int /*<<< orphan*/ * buf_prepend (struct buffer*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static inline bool
buf_write_prepend(struct buffer *dest, const void *src, int size)
{
    uint8_t *cp = buf_prepend(dest, size);
    if (!cp)
    {
        return false;
    }
    memcpy(cp, src, size);
    return true;
}