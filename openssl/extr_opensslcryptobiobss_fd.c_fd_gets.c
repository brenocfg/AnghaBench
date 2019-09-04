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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ fd_read (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int fd_gets(BIO *bp, char *buf, int size)
{
    int ret = 0;
    char *ptr = buf;
    char *end = buf + size - 1;

    while (ptr < end && fd_read(bp, ptr, 1) > 0) {
        if (*ptr++ == '\n')
           break;
    }

    ptr[0] = '\0';

    if (buf[0] != '\0')
        ret = strlen(buf);
    return ret;
}