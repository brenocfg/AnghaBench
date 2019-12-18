#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ strbuf ;

/* Variables and functions */
 TYPE_1__* sb_get (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static strbuf *
savestr(strbuf *sb, const char *str) {
    int len = strlen(str);
    if (sb == 0 || len >= sb->size) {
        sb = sb_get(sb, len + 1);
    }
    strcpy(sb->str, str);
    return sb;
}