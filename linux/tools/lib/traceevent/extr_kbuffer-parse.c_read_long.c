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
struct kbuffer {unsigned long long (* read_long ) (struct kbuffer*,void*) ;} ;

/* Variables and functions */
 unsigned long long stub1 (struct kbuffer*,void*) ; 

__attribute__((used)) static unsigned long long read_long(struct kbuffer *kbuf, void *ptr)
{
	return kbuf->read_long(kbuf, ptr);
}