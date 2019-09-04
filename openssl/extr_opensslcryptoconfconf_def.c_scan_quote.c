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
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 scalar_t__ IS_EOF (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_ESC (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static char *scan_quote(CONF *conf, char *p)
{
    int q = *p;

    p++;
    while (!(IS_EOF(conf, *p)) && (*p != q)) {
        if (IS_ESC(conf, *p)) {
            p++;
            if (IS_EOF(conf, *p))
                return p;
        }
        p++;
    }
    if (*p == q)
        p++;
    return p;
}