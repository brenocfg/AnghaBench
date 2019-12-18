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
typedef  int /*<<< orphan*/  u32 ;
struct rb_info {int /*<<< orphan*/  board_name; } ;
struct rb_board_info {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rb_board_info*) ; 
 struct rb_board_info* rb92x_boards ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rb92x_get_flags(const struct rb_info *info)
{
        int i;

        for (i = 0; i < ARRAY_SIZE(rb92x_boards); i++) {
                const struct rb_board_info *bi;

                bi = &rb92x_boards[i];
                if (strcmp(info->board_name, bi->name) == 0)
                        return bi->flags;
        }

        return 0;
}