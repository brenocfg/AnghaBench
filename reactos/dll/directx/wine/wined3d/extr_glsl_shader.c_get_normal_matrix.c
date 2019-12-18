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
struct wined3d_matrix {float _11; } ;
struct wined3d_context {TYPE_1__* d3d_info; } ;
struct TYPE_2__ {int wined3d_creation_flags; } ;

/* Variables and functions */
 int WINED3D_LEGACY_FFP_LIGHTING ; 
 int /*<<< orphan*/  invert_matrix (struct wined3d_matrix*,struct wined3d_matrix*) ; 
 int /*<<< orphan*/  invert_matrix_3d (struct wined3d_matrix*,struct wined3d_matrix*) ; 

__attribute__((used)) static void get_normal_matrix(struct wined3d_context *context, struct wined3d_matrix *mat, float *normal)
{
    int i, j;

    if (context->d3d_info->wined3d_creation_flags & WINED3D_LEGACY_FFP_LIGHTING)
        invert_matrix_3d(mat, mat);
    else
        invert_matrix(mat, mat);
    /* Tests show that singular modelview matrices are used unchanged as normal
     * matrices on D3D3 and older. There seems to be no clearly consistent
     * behavior on newer D3D versions so always follow older ddraw behavior. */
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            normal[i * 3 + j] = (&mat->_11)[j * 4 + i];
}