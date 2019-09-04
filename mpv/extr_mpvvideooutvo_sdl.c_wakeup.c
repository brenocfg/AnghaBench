#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  wakeup_event; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_PushEvent (TYPE_1__*) ; 

__attribute__((used)) static void wakeup(struct vo *vo)
{
    struct priv *vc = vo->priv;
    SDL_Event event = {.type = vc->wakeup_event};
    // Note that there is no context - SDL is a singleton.
    SDL_PushEvent(&event);
}