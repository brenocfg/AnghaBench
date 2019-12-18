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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * window; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_renderer (struct vo*) ; 
 int /*<<< orphan*/  talloc_free (struct priv*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *vc = vo->priv;
    destroy_renderer(vo);
    SDL_DestroyWindow(vc->window);
    vc->window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    talloc_free(vc);
}