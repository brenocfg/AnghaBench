#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ h; scalar_t__ v; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_1__ report_mouse_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mouse ; 
 int /*<<< orphan*/  phex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  print_hex8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ps2_mouse_print_report(report_mouse_t *mouse_report) {
    if (!debug_mouse) return;
    print("ps2_mouse: [");
    phex(mouse_report->buttons);
    print("|");
    print_hex8((uint8_t)mouse_report->x);
    print(" ");
    print_hex8((uint8_t)mouse_report->y);
    print(" ");
    print_hex8((uint8_t)mouse_report->v);
    print(" ");
    print_hex8((uint8_t)mouse_report->h);
    print("]\n");
}