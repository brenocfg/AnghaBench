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
 int BIO_FLAGS_RWS ; 
 int BIO_FLAGS_SHOULD_RETRY ; 
 int /*<<< orphan*/  BIO_clear_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int) ; 
 int BIO_test_flags (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_flags(BIO *bio)
{
    int flags;
    BIO *next = BIO_next(bio);

    flags = BIO_test_flags(next, BIO_FLAGS_SHOULD_RETRY | BIO_FLAGS_RWS);
    BIO_clear_flags(bio, BIO_FLAGS_SHOULD_RETRY | BIO_FLAGS_RWS);
    BIO_set_flags(bio, flags);
}