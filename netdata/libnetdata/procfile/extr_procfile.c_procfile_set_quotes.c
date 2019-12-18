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
struct TYPE_3__ {scalar_t__* separators; } ;
typedef  TYPE_1__ procfile ;
typedef  scalar_t__ PF_CHAR_TYPE ;

/* Variables and functions */
 scalar_t__ PF_CHAR_IS_QUOTE ; 
 scalar_t__ PF_CHAR_IS_WORD ; 
 scalar_t__ unlikely (int) ; 

void procfile_set_quotes(procfile *ff, const char *quotes) {
    PF_CHAR_TYPE *ffs = ff->separators;

    // remove all quotes
    int i = 256;
    while(i--)
        if(unlikely(ffs[i] == PF_CHAR_IS_QUOTE))
            ffs[i] = PF_CHAR_IS_WORD;

    // if nothing given, return
    if(unlikely(!quotes || !*quotes))
        return;

    // set the quotes
    const char *s = quotes;
    while(*s)
        ffs[(int)*s++] = PF_CHAR_IS_QUOTE;
}