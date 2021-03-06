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
typedef  int GLuint ;

/* Variables and functions */

__attribute__((used)) static int computeLog(GLuint value)
{
    int i;

    i = 0;

    /* Error! */
    if (value == 0) return -1;

    for (;;) {
	if (value & 1) {
	    /* Error ! */
	    if (value != 1) return -1;
	    return i;
	}
	value = value >> 1;
	i++;
    }
}