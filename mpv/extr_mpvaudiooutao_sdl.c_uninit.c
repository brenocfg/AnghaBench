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
struct priv {int dummy; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_LockAudio () ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_WasInit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *priv = ao->priv;
    if (!priv)
        return;

    if (SDL_WasInit(SDL_INIT_AUDIO)) {
        // make sure the callback exits
        SDL_LockAudio();

        // close audio device
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}