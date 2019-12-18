#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  h; int /*<<< orphan*/  v; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  buttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mouse ; 
 TYPE_1__ mouse_report ; 
 int /*<<< orphan*/  mousekey_accel ; 
 int /*<<< orphan*/  mousekey_repeat ; 
 int /*<<< orphan*/  phex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  print_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_decs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mousekey_debug(void) {
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h](rep/acl): [");
    phex(mouse_report.buttons);
    print("|");
    print_decs(mouse_report.x);
    print(" ");
    print_decs(mouse_report.y);
    print(" ");
    print_decs(mouse_report.v);
    print(" ");
    print_decs(mouse_report.h);
    print("](");
    print_dec(mousekey_repeat);
    print("/");
    print_dec(mousekey_accel);
    print(")\n");
}