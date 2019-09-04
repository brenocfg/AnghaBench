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
struct base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMBER1 ; 
 int /*<<< orphan*/  NUMBER10 ; 
 int /*<<< orphan*/  NUMBER11 ; 
 int /*<<< orphan*/  NUMBER2 ; 
 int /*<<< orphan*/  NUMBER3 ; 
 int /*<<< orphan*/  NUMBER4 ; 
 int /*<<< orphan*/  NUMBER5 ; 
 int /*<<< orphan*/  NUMBER6 ; 
 int /*<<< orphan*/  NUMBER7 ; 
 int /*<<< orphan*/  NUMBER8 ; 
 int /*<<< orphan*/  NUMBER9 ; 
 int /*<<< orphan*/  begin (struct base*) ; 
 int /*<<< orphan*/  callback ; 
 scalar_t__ check (struct base*,scalar_t__) ; 
 struct base* entry (struct base*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* strings ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * values6 ; 

void test7() {

    static struct base *base = NULL;

    if(unlikely(!base)) {
        base = entry(base, "cache", NUMBER1, &values6[0], callback);
        base = entry(base, "rss", NUMBER2, &values6[1], callback);
        base = entry(base, "rss_huge", NUMBER3, &values6[2], callback);
        base = entry(base, "mapped_file", NUMBER4, &values6[3], callback);
        base = entry(base, "writeback", NUMBER5, &values6[4], callback);
        base = entry(base, "dirty", NUMBER6, &values6[5], callback);
        base = entry(base, "swap", NUMBER7, &values6[6], callback);
        base = entry(base, "pgpgin", NUMBER8, &values6[7], callback);
        base = entry(base, "pgpgout", NUMBER9, &values6[8], callback);
        base = entry(base, "pgfault", NUMBER10, &values6[9], callback);
        base = entry(base, "pgmajfault", NUMBER11, &values6[10], callback);
    }

    begin(base);

    int i;
    for(i = 0; strings[i] ; i++) {
        if(check(base, strings[i]))
            break;
    }
}