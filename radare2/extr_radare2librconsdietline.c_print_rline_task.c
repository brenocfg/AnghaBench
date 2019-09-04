#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ buffer; int /*<<< orphan*/  prompt; } ;

/* Variables and functions */
 int /*<<< orphan*/  Color_RESET ; 
 TYPE_2__ I ; 
 int /*<<< orphan*/  r_cons_clear_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_rline_task(void *core) {
	r_cons_clear_line (0);
	r_cons_printf ("%s%s%s", Color_RESET, I.prompt,  I.buffer.data); 
	r_cons_flush ();
}