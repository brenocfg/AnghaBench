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
struct gs_vb_data {int dummy; } ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
struct TYPE_3__ {struct gs_vb_data* (* gs_vertexbuffer_get_data ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_4__ {TYPE_1__ exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 struct gs_vb_data* stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

struct gs_vb_data *gs_vertexbuffer_get_data(const gs_vertbuffer_t *vertbuffer)
{
	if (!gs_valid_p("gs_vertexbuffer_get_data", vertbuffer))
		return NULL;

	return thread_graphics->exports.gs_vertexbuffer_get_data(vertbuffer);
}