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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_puts (int /*<<< orphan*/ *,char*) ; 

int BIO_indent(BIO *b, int indent, int max)
{
    if (indent < 0)
        indent = 0;
    if (indent > max)
        indent = max;
    while (indent--)
        if (BIO_puts(b, " ") != 1)
            return 0;
    return 1;
}