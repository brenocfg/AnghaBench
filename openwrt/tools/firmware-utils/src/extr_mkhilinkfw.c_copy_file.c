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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_file(int src, int dst)
{
	char buf[4096];
	ssize_t size;
 
	while ((size = read(src, buf, 4096)) > 0) {
        write(dst, buf, size);
    }
}