#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gs_indexbuffer_t ;
struct TYPE_3__ {size_t (* gs_indexbuffer_get_num_indices ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_4__ {TYPE_1__ exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 size_t stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

size_t gs_indexbuffer_get_num_indices(const gs_indexbuffer_t *indexbuffer)
{
	if (!gs_valid_p("gs_indexbuffer_get_num_indices", indexbuffer))
		return 0;

	return thread_graphics->exports.gs_indexbuffer_get_num_indices(
		indexbuffer);
}