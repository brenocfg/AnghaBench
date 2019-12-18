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
 int /*<<< orphan*/  buf_write (struct buffer*,char const*,int const) ; 
 int /*<<< orphan*/  buf_write_u16 (struct buffer*,int const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool
write_string(struct buffer *buf, const char *str, const int maxlen)
{
    const int len = strlen(str) + 1;
    if (len < 1 || (maxlen >= 0 && len > maxlen))
    {
        return false;
    }
    if (!buf_write_u16(buf, len))
    {
        return false;
    }
    if (!buf_write(buf, str, len))
    {
        return false;
    }
    return true;
}