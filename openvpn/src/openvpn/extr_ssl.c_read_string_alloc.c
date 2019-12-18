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
 int /*<<< orphan*/  check_malloc_return (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int const) ; 

__attribute__((used)) static char *
read_string_alloc(struct buffer *buf)
{
    const int len = buf_read_u16(buf);
    char *str;

    if (len < 1)
    {
        return NULL;
    }
    str = (char *) malloc(len);
    check_malloc_return(str);
    if (!buf_read(buf, str, len))
    {
        free(str);
        return NULL;
    }
    str[len-1] = '\0';
    return str;
}