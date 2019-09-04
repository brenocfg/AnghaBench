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
typedef  int /*<<< orphan*/  symbols ;
typedef  int /*<<< orphan*/  BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BN_GENCB_get_arg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dsa_cb(int p, int n, BN_GENCB *cb)
{
    static const char symbols[] = ".+*\n";
    char c = (p >= 0 && (size_t)p < sizeof(symbols) - 1) ? symbols[p] : '?';

    if (!verbose)
        return 1;

    BIO_write(BN_GENCB_get_arg(cb), &c, 1);
    (void)BIO_flush(BN_GENCB_get_arg(cb));
    return 1;
}