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

/* Variables and functions */
 int /*<<< orphan*/  SDL_DisableScreenSaver () ; 
 int /*<<< orphan*/  SDL_EnableScreenSaver () ; 
 int /*<<< orphan*/  SDL_IsScreenSaverEnabled () ; 

__attribute__((used)) static inline void set_screensaver(bool enabled)
{
    if (!!enabled == !!SDL_IsScreenSaverEnabled())
        return;

    if (enabled)
        SDL_EnableScreenSaver();
    else
        SDL_DisableScreenSaver();
}