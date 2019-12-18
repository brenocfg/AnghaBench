#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gs_vb_data {int dummy; } ;
struct TYPE_3__ {struct gs_vb_data* data; } ;
typedef  TYPE_1__ gs_vertbuffer_t ;

/* Variables and functions */

struct gs_vb_data *gs_vertexbuffer_get_data(const gs_vertbuffer_t *vb)
{
	return vb->data;
}