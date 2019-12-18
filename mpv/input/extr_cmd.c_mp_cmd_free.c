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
typedef  int /*<<< orphan*/  mp_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

void mp_cmd_free(mp_cmd_t *cmd)
{
    talloc_free(cmd);
}