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
 int BIO_write (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int write_bio(const void *data, size_t len, void *bp)
{
    return BIO_write((BIO *)bp, (const char *)data, len);
}