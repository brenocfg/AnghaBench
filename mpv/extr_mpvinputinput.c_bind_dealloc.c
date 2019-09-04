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
struct cmd_bind {int /*<<< orphan*/  location; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bind_dealloc(struct cmd_bind *bind)
{
    talloc_free(bind->cmd);
    talloc_free(bind->location);
}