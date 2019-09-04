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
 int __copy_page (int,unsigned long,int) ; 

__attribute__((used)) static int copy_page(int ufd, unsigned long offset)
{
	return __copy_page(ufd, offset, false);
}