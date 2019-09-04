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
 scalar_t__ glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_input_unicode (struct nk_context*,unsigned int) ; 

__attribute__((used)) static void text_input(GLFWwindow *win, unsigned int codepoint)
{nk_input_unicode((struct nk_context*)glfwGetWindowUserPointer(win), codepoint);}