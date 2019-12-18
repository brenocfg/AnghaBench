#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; } ;
typedef  TYPE_1__ strbuf ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mymalloc (int) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static strbuf *
sb_get(strbuf *sb, int len) {
    int size;
    for (size = 128; size < len; size += size)
        ;
    if (sb == 0) {
        sb = (strbuf *) mymalloc(sizeof(*sb) + size);
    }
    else {
        sb = (strbuf *) realloc(sb, sizeof(*sb) + size);
        if (sb == 0) {
            fputs("C CGI Library out of memory\n", stderr);
            exit(1);
        }
    }
    sb->size = size;
    return sb;
}