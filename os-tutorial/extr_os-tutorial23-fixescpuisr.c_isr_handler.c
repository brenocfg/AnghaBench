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
struct TYPE_3__ {size_t int_no; } ;
typedef  TYPE_1__ registers_t ;

/* Variables and functions */
 char** exception_messages ; 
 int /*<<< orphan*/  int_to_ascii (size_t,char*) ; 
 int /*<<< orphan*/  kprint (char*) ; 

void isr_handler(registers_t *r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r->int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r->int_no]);
    kprint("\n");
}