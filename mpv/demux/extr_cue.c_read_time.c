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
struct bstr {int dummy; } ;

/* Variables and functions */
 double SECS_PER_CUE_FRAME ; 
 scalar_t__ eat_char (struct bstr*,char) ; 
 double read_int (struct bstr*,int) ; 

__attribute__((used)) static double read_time(struct bstr *data)
{
    struct bstr s = *data;
    bool ok = true;
    double t1 = read_int(&s, false);
    ok = eat_char(&s, ':') && ok;
    double t2 = read_int(&s, true);
    ok = eat_char(&s, ':') && ok;
    double t3 = read_int(&s, true);
    ok = ok && t1 >= 0 && t2 >= 0 && t3 >= 0;
    return ok ? t1 * 60.0 + t2 + t3 * SECS_PER_CUE_FRAME : 0;
}