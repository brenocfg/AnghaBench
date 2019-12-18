#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* lines; TYPE_1__* words; } ;
typedef  TYPE_4__ procfile ;
struct TYPE_12__ {size_t len; TYPE_2__* lines; } ;
struct TYPE_11__ {size_t first; char* words; } ;
struct TYPE_10__ {char* len; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROCFILE ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t,size_t,char*) ; 
 scalar_t__ likely (int) ; 
 size_t procfile_filename (TYPE_4__*) ; 
 size_t procfile_lines (TYPE_4__*) ; 
 char* procfile_lineword (TYPE_4__*,size_t,size_t) ; 
 size_t procfile_linewords (TYPE_4__*,size_t) ; 

void procfile_print(procfile *ff) {
    size_t lines = procfile_lines(ff), l;
    char *s;
    (void)s;

    debug(D_PROCFILE, "File '%s' with %zu lines and %zu words", procfile_filename(ff), ff->lines->len, ff->words->len);

    for(l = 0; likely(l < lines) ;l++) {
        size_t words = procfile_linewords(ff, l);

        debug(D_PROCFILE, " line %zu starts at word %zu and has %zu words", l, ff->lines->lines[l].first, ff->lines->lines[l].words);

        size_t w;
        for(w = 0; likely(w < words) ;w++) {
            s = procfile_lineword(ff, l, w);
            debug(D_PROCFILE, "     [%zu.%zu] '%s'", l, w, s);
        }
    }
}