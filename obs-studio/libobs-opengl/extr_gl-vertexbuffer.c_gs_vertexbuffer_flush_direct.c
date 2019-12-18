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
struct gs_vb_data {int dummy; } ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_vertexbuffer_flush_internal (int /*<<< orphan*/ *,struct gs_vb_data const*) ; 

void gs_vertexbuffer_flush_direct(gs_vertbuffer_t *vb,
				  const struct gs_vb_data *data)
{
	gs_vertexbuffer_flush_internal(vb, data);
}