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
struct vo {int dwidth; int dheight; struct priv* priv; } ;
struct priv {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_GetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  resize (struct vo*,int,int) ; 

__attribute__((used)) static void check_resize(struct vo *vo)
{
    struct priv *vc = vo->priv;
    int w, h;
    SDL_GetWindowSize(vc->window, &w, &h);
    if (vo->dwidth != w || vo->dheight != h)
        resize(vo, w, h);
}