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
typedef  int SDL_JoystickID ;
typedef  int /*<<< orphan*/  SDL_Joystick ;
typedef  int /*<<< orphan*/  SDL_GameController ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct mp_input_src*,char*,char const*) ; 
 int /*<<< orphan*/  SDL_GameControllerClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SDL_GameControllerGetJoystick (int /*<<< orphan*/ *) ; 
 char* SDL_GameControllerName (int /*<<< orphan*/ *) ; 
 int SDL_JoystickInstanceID (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_gamepad(struct mp_input_src *src, int id)
{
    struct gamepad_priv *p = src->priv;
    SDL_GameController *controller = p->controller;
    SDL_Joystick* j = SDL_GameControllerGetJoystick(controller);
    SDL_JoystickID jid = SDL_JoystickInstanceID(j);

    if (controller && jid == id) {
        const char *name = SDL_GameControllerName(controller);
        MP_INFO(src, "removed controller: %s\n", name);
        SDL_GameControllerClose(controller);
        p->controller = NULL;
    }
}