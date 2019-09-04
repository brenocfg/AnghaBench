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
 void* espconn_memzalloc (size_t,char*,int) ; 

void *espconn_memcalloc(size_t count, size_t size)
{
	void *cp = NULL;
	cp = espconn_memzalloc(count * size, __FILE__, __LINE__);
	return cp;
}