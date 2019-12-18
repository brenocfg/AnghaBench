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
struct mp_input_src {struct gamepad_priv* priv; } ;
struct gamepad_priv {int /*<<< orphan*/ * controller; } ;
typedef  int /*<<< orphan*/  SDL_GameController ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct mp_input_src*,char*,char const*) ; 
 int /*<<< orphan*/  MP_WARN (struct mp_input_src*,char*) ; 
 char* SDL_GameControllerName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SDL_GameControllerOpen (int) ; 
 scalar_t__ SDL_IsGameController (int) ; 

__attribute__((used)) static void add_gamepad(struct mp_input_src *src, int id)
{
    struct gamepad_priv *p = src->priv;

    if (p->controller) {
        MP_WARN(src, "can't add more than one controller\n");
        return;
    }

    if (SDL_IsGameController(id)) {
        SDL_GameController *controller = SDL_GameControllerOpen(id);

        if (controller) {
            const char *name = SDL_GameControllerName(controller);
            MP_INFO(src, "added controller: %s\n", name);
            p->controller = controller;
            return;
        }
    }
}