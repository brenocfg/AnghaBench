#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ gs_indexbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_indexbuffer_flush_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 

void gs_indexbuffer_flush(gs_indexbuffer_t *ib)
{
	gs_indexbuffer_flush_internal(ib, ib->data);
}