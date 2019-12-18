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
typedef  int /*<<< orphan*/  rand_buf ;

/* Variables and functions */
 int /*<<< orphan*/  RAND_add (unsigned char*,size_t,double) ; 
 int /*<<< orphan*/  RAND_seed (unsigned char*,int) ; 
 int /*<<< orphan*/  RAND_status () ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static int test_rand_add(void)
{
    unsigned char rand_buf[256];
    size_t rand_buflen;

    memset(rand_buf, 0xCD, sizeof(rand_buf));

    /* make sure it's instantiated */
    RAND_seed(rand_buf, sizeof(rand_buf));
    if (!TEST_true(RAND_status()))
        return 0;

    for ( rand_buflen = 256 ; rand_buflen > 0 ; --rand_buflen ) {
        RAND_add(rand_buf, rand_buflen, 0.0);
        if (!TEST_true(RAND_status()))
            return 0;
    }

    return 1;
}