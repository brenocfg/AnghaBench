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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int hash_df (int /*<<< orphan*/ *,unsigned char*,unsigned char const,unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hash_df1(RAND_DRBG *drbg, unsigned char *out,
                    const unsigned char in_byte,
                    const unsigned char *in1, size_t in1len)
{
    return hash_df(drbg, out, in_byte, in1, in1len, NULL, 0, NULL, 0);
}