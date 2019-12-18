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
struct vaapi_gl_mapper_priv {scalar_t__* images; int /*<<< orphan*/  (* DestroyImageKHR ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct ra_hwdec_mapper {struct priv* priv; } ;
struct priv {struct vaapi_gl_mapper_priv* interop_mapper_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  eglGetCurrentDisplay () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vaapi_gl_unmap(struct ra_hwdec_mapper *mapper)
{
    struct priv *p_mapper = mapper->priv;
    struct vaapi_gl_mapper_priv *p = p_mapper->interop_mapper_priv;

    if (p) {
        for (int n = 0; n < 4; n++) {
            if (p->images[n])
                p->DestroyImageKHR(eglGetCurrentDisplay(), p->images[n]);
            p->images[n] = 0;
        }
    }
}