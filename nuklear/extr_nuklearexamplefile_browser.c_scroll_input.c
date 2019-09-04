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
 int /*<<< orphan*/  UNUSED (double) ; 
 scalar_t__ glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_input_scroll (struct nk_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_vec2 (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void scroll_input(GLFWwindow *win, double _, double yoff)
{UNUSED(_);nk_input_scroll((struct nk_context*)glfwGetWindowUserPointer(win), nk_vec2(0, (float)yoff));}