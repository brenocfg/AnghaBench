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
typedef  size_t uint32_t ;
struct gs_vb_data {size_t num_tex; struct gs_vb_data* tvarray; struct gs_vb_data* array; struct gs_vb_data* colors; struct gs_vb_data* tangents; struct gs_vb_data* normals; struct gs_vb_data* points; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct gs_vb_data*) ; 

__attribute__((used)) static inline void gs_vbdata_destroy(struct gs_vb_data *data)
{
	uint32_t i;
	if (!data)
		return;

	bfree(data->points);
	bfree(data->normals);
	bfree(data->tangents);
	bfree(data->colors);
	for (i = 0; i < data->num_tex; i++)
		bfree(data->tvarray[i].array);
	bfree(data->tvarray);
	bfree(data);
}