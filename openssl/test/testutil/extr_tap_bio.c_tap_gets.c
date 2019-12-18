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
 int BIO_gets (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BIO_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tap_gets(BIO *b, char *buf, int size)
{
    return BIO_gets(BIO_next(b), buf, size);
}