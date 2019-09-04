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

/* Variables and functions */
 int /*<<< orphan*/  clear_screen () ; 
 int /*<<< orphan*/  kprint (char*) ; 
 int /*<<< orphan*/  kprint_at (char*,int,int) ; 

void main() {
    clear_screen();
    kprint_at("X", 1, 6);
    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("There is a line\nbreak", 0, 20);
    kprint("There is a line\nbreak");
    kprint_at("What happens when we run out of space?", 45, 24);
}