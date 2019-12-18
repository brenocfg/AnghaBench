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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int write (int,unsigned char*,int) ; 

__attribute__((used)) static int
send_control(int fd, int code)
{
    unsigned char c = (unsigned char) code;
    const ssize_t size = write(fd, &c, sizeof(c));
    if (size == sizeof(c))
    {
        return (int) size;
    }
    else
    {
        return -1;
    }
}