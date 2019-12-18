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
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_PRINT_PRIVATE ; 
 int /*<<< orphan*/  EC_KEY_PRINT_PUBLIC ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (int /*<<< orphan*/  const*) ; 
 int do_EC_KEY_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

int EC_KEY_print(BIO *bp, const EC_KEY *x, int off)
{
    int private = EC_KEY_get0_private_key(x) != NULL;

    return do_EC_KEY_print(bp, x, off,
                private ? EC_KEY_PRINT_PRIVATE : EC_KEY_PRINT_PUBLIC);
}