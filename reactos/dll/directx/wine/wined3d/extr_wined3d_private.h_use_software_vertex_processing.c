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
struct TYPE_2__ {int flags; } ;
struct wined3d_device {int /*<<< orphan*/  softwareVertexProcessing; TYPE_1__ create_parms; int /*<<< orphan*/ * shader_backend; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int WINED3DCREATE_MIXED_VERTEXPROCESSING ; 
 int WINED3DCREATE_SOFTWARE_VERTEXPROCESSING ; 
 int /*<<< orphan*/  glsl_shader_backend ; 

__attribute__((used)) static inline BOOL use_software_vertex_processing(const struct wined3d_device *device)
{
    if (device->shader_backend != &glsl_shader_backend)
        return FALSE;

    if (device->create_parms.flags & WINED3DCREATE_SOFTWARE_VERTEXPROCESSING)
        return TRUE;

    if (!(device->create_parms.flags & WINED3DCREATE_MIXED_VERTEXPROCESSING))
        return FALSE;

    return device->softwareVertexProcessing;
}