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
struct ParseTypedefData {char* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int stabs_pts_read_number(struct ParseTypedefData* ptd, long* v)
{
    char*	last;

    *v = strtol(ptd->ptr, &last, 10);
    PTS_ABORTIF(ptd, last == ptd->ptr);
    ptd->ptr = last;
    return 0;
}