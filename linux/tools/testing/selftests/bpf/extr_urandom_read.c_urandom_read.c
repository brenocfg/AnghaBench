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

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  read (int,char*,int) ; 

__attribute__((used)) static __attribute__((noinline))
void urandom_read(int fd, int count)
{
       char buf[BUF_SIZE];
       int i;

       for (i = 0; i < count; ++i)
               read(fd, buf, BUF_SIZE);
}