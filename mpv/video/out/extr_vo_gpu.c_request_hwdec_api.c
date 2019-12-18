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
struct vo {int /*<<< orphan*/  hwdec_devs; struct gpu_priv* priv; } ;
struct gpu_priv {int /*<<< orphan*/  renderer; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_load_hwdecs_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void request_hwdec_api(struct vo *vo)
{
    struct gpu_priv *p = vo->priv;

    gl_video_load_hwdecs_all(p->renderer, vo->hwdec_devs);
}