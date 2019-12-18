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
struct TYPE_6__ {int size; int* str; } ;
typedef  TYPE_1__ strbuf ;

/* Variables and functions */
 TYPE_1__* sb_get (TYPE_1__*,int) ; 

__attribute__((used)) static strbuf *
savechar(strbuf *sb, int idx, int c) {
    if (sb == 0 || idx >= sb->size) {
        sb = sb_get(sb, idx + 1);
    }
    sb->str[idx] = c;
    return sb;
}