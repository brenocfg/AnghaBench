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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_lebin2bn (unsigned char const*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_lebn(const unsigned char **in, unsigned int nbyte, BIGNUM **r)
{
    *r = BN_lebin2bn(*in, nbyte, NULL);
    if (*r == NULL)
        return 0;
    *in += nbyte;
    return 1;
}