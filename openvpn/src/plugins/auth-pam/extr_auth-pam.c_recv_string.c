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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int
recv_string(int fd, char *buffer, int len)
{
    if (len > 0)
    {
        ssize_t size;
        memset(buffer, 0, len);
        size = read(fd, buffer, len);
        buffer[len-1] = 0;
        if (size >= 1)
        {
            return (int)size;
        }
    }
    return -1;
}