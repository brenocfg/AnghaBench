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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CRNGT_BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 scalar_t__ crngt_get_entropy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * crngt_pool ; 
 int /*<<< orphan*/  crngt_prev ; 
 int /*<<< orphan*/  rand_crngt_cleanup () ; 
 int /*<<< orphan*/ * rand_pool_new (int /*<<< orphan*/ ,int,int) ; 

int rand_crngt_init(void)
{
    unsigned char buf[CRNGT_BUFSIZ];

    if ((crngt_pool = rand_pool_new(0, CRNGT_BUFSIZ, CRNGT_BUFSIZ)) == NULL)
        return 0;
    if (crngt_get_entropy(buf, crngt_prev, NULL)) {
        OPENSSL_cleanse(buf, sizeof(buf));
        return 1;
    }
    rand_crngt_cleanup();
    return 0;
}