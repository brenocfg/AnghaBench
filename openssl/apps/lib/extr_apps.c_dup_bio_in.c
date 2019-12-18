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
 int BIO_FP_TEXT ; 
 int BIO_NOCLOSE ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ FMT_istext (int) ; 
 int /*<<< orphan*/  stdin ; 

BIO *dup_bio_in(int format)
{
    return BIO_new_fp(stdin,
                      BIO_NOCLOSE | (FMT_istext(format) ? BIO_FP_TEXT : 0));
}