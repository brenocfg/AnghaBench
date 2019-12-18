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
struct shader_none_priv {int /*<<< orphan*/  ffp_proj_control; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL shader_none_has_ffp_proj_control(void *shader_priv)
{
    struct shader_none_priv *priv = shader_priv;

    return priv->ffp_proj_control;
}