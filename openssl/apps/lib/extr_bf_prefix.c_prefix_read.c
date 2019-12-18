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
 int /*<<< orphan*/  BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read_ex (int /*<<< orphan*/ ,char*,size_t,size_t*) ; 

__attribute__((used)) static int prefix_read(BIO *b, char *in, size_t size, size_t *numread)
{
    return BIO_read_ex(BIO_next(b), in, size, numread);
}