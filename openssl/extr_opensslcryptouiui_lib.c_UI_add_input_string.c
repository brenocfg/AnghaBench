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
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  UIT_PROMPT ; 
 int general_allocate_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int,int /*<<< orphan*/ *) ; 

int UI_add_input_string(UI *ui, const char *prompt, int flags,
                        char *result_buf, int minsize, int maxsize)
{
    return general_allocate_string(ui, prompt, 0,
                                   UIT_PROMPT, flags, result_buf, minsize,
                                   maxsize, NULL);
}