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
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 TYPE_1__* f2py_foodata_def ; 

__attribute__((used)) static void f2py_setup_foodata(char *a,char *b,char *c) {
    f2py_foodata_def[0].data = a;
    f2py_foodata_def[1].data = b;
    f2py_foodata_def[2].data = c;
}