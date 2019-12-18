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
struct TYPE_3__ {int bytelen; } ;
typedef  TYPE_1__ ByteProg ;

/* Variables and functions */
 int /*<<< orphan*/  NON_ANCHORED_PREFIX ; 
 int /*<<< orphan*/ * _compilecode (char const*,TYPE_1__*,int) ; 

int re1_5_sizecode(const char *re)
{
    ByteProg dummyprog = {
         // Save 0, Save 1, Match; more bytes for "search" (vs "match") prefix code
        .bytelen = 5 + NON_ANCHORED_PREFIX
    };

    if (_compilecode(re, &dummyprog, /*sizecode*/1) == NULL) return -1;

    return dummyprog.bytelen;
}