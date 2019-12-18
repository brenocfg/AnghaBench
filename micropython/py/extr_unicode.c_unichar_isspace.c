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
typedef  int unichar ;

/* Variables and functions */
 int FL_SPACE ; 
 int* attr ; 

bool unichar_isspace(unichar c) {
    return c < 128 && (attr[c] & FL_SPACE) != 0;
}