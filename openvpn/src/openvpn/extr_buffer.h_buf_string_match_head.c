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
struct buffer {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPTR (struct buffer const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static inline bool
buf_string_match_head(const struct buffer *src, const void *match, int size)
{
    if (size < 0 || size > src->len)
    {
        return false;
    }
    return memcmp(BPTR(src), match, size) == 0;
}