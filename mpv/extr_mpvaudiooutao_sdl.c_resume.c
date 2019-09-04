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
struct priv {scalar_t__ paused; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FALSE ; 
 int /*<<< orphan*/  SDL_PauseAudio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resume(struct ao *ao)
{
    struct priv *priv = ao->priv;
    if (priv->paused)
        SDL_PauseAudio(SDL_FALSE);
    priv->paused = 0;
}