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
 int /*<<< orphan*/  buf_read (struct buffer*,char*,int const) ; 
 int buf_read_u16 (struct buffer*) ; 

__attribute__((used)) static bool
read_string(struct buffer *buf, char *str, const unsigned int capacity)
{
    const int len = buf_read_u16(buf);
    if (len < 1 || len > (int)capacity)
    {
        return false;
    }
    if (!buf_read(buf, str, len))
    {
        return false;
    }
    str[len-1] = '\0';
    return true;
}