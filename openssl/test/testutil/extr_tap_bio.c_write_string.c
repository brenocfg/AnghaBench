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
 scalar_t__ BIO_write_ex (int /*<<< orphan*/ *,char const*,size_t,size_t*) ; 

__attribute__((used)) static int write_string(BIO *b, const char *buf, size_t n)
{
    size_t m;

    return BIO_write_ex(b, buf, n, &m) != 0 && m == n;
}