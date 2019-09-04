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
struct stat {scalar_t__ st_mode; } ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int mch_stat (int /*<<< orphan*/ *,struct stat*) ; 

long
mch_getperm(char_u *name)
{
    struct stat st;
    int		n;

    n = mch_stat(name, &st);
    return n == 0 ? (long)(unsigned short)st.st_mode : -1L;
}