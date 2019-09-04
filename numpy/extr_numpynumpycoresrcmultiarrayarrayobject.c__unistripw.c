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
typedef  scalar_t__ npy_ucs4 ;

/* Variables and functions */
 scalar_t__ NumPyOS_ascii_isspace (int) ; 

__attribute__((used)) static void _unistripw(npy_ucs4 *s, int n)
{
    int i;
    for (i = n - 1; i >= 1; i--) { /* Never strip to length 0. */
        npy_ucs4 c = s[i];
        if (!c || NumPyOS_ascii_isspace((int)c)) {
            s[i] = 0;
        }
        else {
            break;
        }
    }
}