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
struct TYPE_3__ {int /*<<< orphan*/ * separators; } ;
typedef  TYPE_1__ procfile ;
typedef  int /*<<< orphan*/  PF_CHAR_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  PF_CHAR_IS_NEWLINE ; 
 int /*<<< orphan*/  PF_CHAR_IS_SEPARATOR ; 
 int /*<<< orphan*/  PF_CHAR_IS_WORD ; 
 int /*<<< orphan*/  isprint (int) ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void procfile_set_separators(procfile *ff, const char *separators) {
    static PF_CHAR_TYPE def[256];
    static char initilized = 0;

    if(unlikely(!initilized)) {
        // this is thread safe
        // if initialized is zero, multiple threads may be executing
        // this code at the same time, setting in def[] the exact same values
        int i = 256;
        while(i--) {
            if(unlikely(i == '\n' || i == '\r'))
                def[i] = PF_CHAR_IS_NEWLINE;

            else if(unlikely(isspace(i) || !isprint(i)))
                def[i] = PF_CHAR_IS_SEPARATOR;

            else
                def[i] = PF_CHAR_IS_WORD;
        }

        initilized = 1;
    }

    // copy the default
    PF_CHAR_TYPE *ffs = ff->separators, *ffd = def, *ffe = &def[256];
    while(ffd != ffe)
        *ffs++ = *ffd++;

    // set the separators
    if(unlikely(!separators))
        separators = " \t=|";

    ffs = ff->separators;
    const char *s = separators;
    while(*s)
        ffs[(int)*s++] = PF_CHAR_IS_SEPARATOR;
}