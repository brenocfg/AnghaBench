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
struct nk_context {int dummy; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_KEY_BACKSPACE ; 
 int /*<<< orphan*/  GLFW_KEY_C ; 
 int /*<<< orphan*/  GLFW_KEY_DELETE ; 
 int /*<<< orphan*/  GLFW_KEY_DOWN ; 
 int /*<<< orphan*/  GLFW_KEY_E ; 
 int /*<<< orphan*/  GLFW_KEY_ENTER ; 
 int /*<<< orphan*/  GLFW_KEY_LEFT ; 
 int /*<<< orphan*/  GLFW_KEY_LEFT_CONTROL ; 
 int /*<<< orphan*/  GLFW_KEY_P ; 
 int /*<<< orphan*/  GLFW_KEY_RIGHT ; 
 int /*<<< orphan*/  GLFW_KEY_RIGHT_CONTROL ; 
 int /*<<< orphan*/  GLFW_KEY_TAB ; 
 int /*<<< orphan*/  GLFW_KEY_UP ; 
 int /*<<< orphan*/  GLFW_KEY_X ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_LEFT ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  GLFW_MOUSE_BUTTON_RIGHT ; 
 scalar_t__ GLFW_PRESS ; 
 int /*<<< orphan*/  NK_BUTTON_LEFT ; 
 int /*<<< orphan*/  NK_BUTTON_MIDDLE ; 
 int /*<<< orphan*/  NK_BUTTON_RIGHT ; 
 int /*<<< orphan*/  NK_KEY_BACKSPACE ; 
 int /*<<< orphan*/  NK_KEY_COPY ; 
 int /*<<< orphan*/  NK_KEY_CUT ; 
 int /*<<< orphan*/  NK_KEY_DEL ; 
 int /*<<< orphan*/  NK_KEY_DOWN ; 
 int /*<<< orphan*/  NK_KEY_ENTER ; 
 int /*<<< orphan*/  NK_KEY_LEFT ; 
 int /*<<< orphan*/  NK_KEY_PASTE ; 
 int /*<<< orphan*/  NK_KEY_RIGHT ; 
 int /*<<< orphan*/  NK_KEY_SHIFT ; 
 int /*<<< orphan*/  NK_KEY_TAB ; 
 int /*<<< orphan*/  NK_KEY_UP ; 
 int /*<<< orphan*/  glfwGetCursorPos (int /*<<< orphan*/ *,double*,double*) ; 
 scalar_t__ glfwGetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ glfwGetMouseButton (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  nk_input_begin (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_button (struct nk_context*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nk_input_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_input_key (struct nk_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_input_motion (struct nk_context*,int,int) ; 

__attribute__((used)) static void
pump_input(struct nk_context *ctx, GLFWwindow *win)
{
    double x, y;
    nk_input_begin(ctx);
    glfwPollEvents();

    nk_input_key(ctx, NK_KEY_DEL, glfwGetKey(win, GLFW_KEY_DELETE) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_ENTER, glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_TAB, glfwGetKey(win, GLFW_KEY_TAB) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_BACKSPACE, glfwGetKey(win, GLFW_KEY_BACKSPACE) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_LEFT, glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_RIGHT, glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_UP, glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_DOWN, glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS);

    if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
        glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
        nk_input_key(ctx, NK_KEY_COPY, glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS);
        nk_input_key(ctx, NK_KEY_PASTE, glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS);
        nk_input_key(ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS);
        nk_input_key(ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS);
        nk_input_key(ctx, NK_KEY_SHIFT, 1);
    } else {
        nk_input_key(ctx, NK_KEY_COPY, 0);
        nk_input_key(ctx, NK_KEY_PASTE, 0);
        nk_input_key(ctx, NK_KEY_CUT, 0);
        nk_input_key(ctx, NK_KEY_SHIFT, 0);
    }

    glfwGetCursorPos(win, &x, &y);
    nk_input_motion(ctx, (int)x, (int)y);
    nk_input_button(ctx, NK_BUTTON_LEFT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_MIDDLE, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_RIGHT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
    nk_input_end(ctx);
}