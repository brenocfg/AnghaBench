#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSHM_DATA (void*) ; 
 TYPE_1__* data ; 

__attribute__((used)) static uint32_t xshm_getwidth(void *vptr)
{
	XSHM_DATA(vptr);
	return data->width;
}