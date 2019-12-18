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
typedef  int /*<<< orphan*/  d3d_priv ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  destroy_d3d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_d3d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resize_d3d (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reconfigure_d3d(d3d_priv *priv)
{
    MP_VERBOSE(priv, "reconfigure_d3d called.\n");

    // Force complete destruction of the D3D state.
    // Note: this step could be omitted. The resize_d3d call below would detect
    // that d3d_device is NULL, and would properly recreate it. I'm not sure why
    // the following code to release and recreate the d3d_handle exists.
    destroy_d3d(priv);
    if (!init_d3d(priv))
        return 0;

    // Proper re-initialization.
    if (!resize_d3d(priv))
        return 0;

    return 1;
}