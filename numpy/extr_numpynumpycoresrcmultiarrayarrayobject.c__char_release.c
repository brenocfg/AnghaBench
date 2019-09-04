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
 int SMALL_STRING ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
_char_release(char *ptr, int nc)
{
    if (nc > SMALL_STRING) {
        free(ptr);
    }
}