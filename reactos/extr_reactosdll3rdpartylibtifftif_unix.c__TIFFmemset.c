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
typedef  scalar_t__ tmsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

void
_TIFFmemset(void* p, int v, tmsize_t c)
{
	memset(p, v, (size_t) c);
}