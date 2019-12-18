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
typedef  enum gs_index_type { ____Placeholder_gs_index_type } gs_index_type ;
struct TYPE_3__ {int (* gs_indexbuffer_get_type ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_4__ {TYPE_1__ exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 int stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

enum gs_index_type gs_indexbuffer_get_type(const gs_indexbuffer_t *indexbuffer)
{
	if (!gs_valid_p("gs_indexbuffer_get_type", indexbuffer))
		return (enum gs_index_type)0;

	return thread_graphics->exports.gs_indexbuffer_get_type(indexbuffer);
}