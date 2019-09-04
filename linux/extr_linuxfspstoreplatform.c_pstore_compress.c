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

/* Variables and functions */
 int crypto_comp_compress (int /*<<< orphan*/ ,void const*,unsigned int,void*,unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  tfm ; 

__attribute__((used)) static int pstore_compress(const void *in, void *out,
			   unsigned int inlen, unsigned int outlen)
{
	int ret;

	ret = crypto_comp_compress(tfm, in, inlen, out, &outlen);
	if (ret) {
		pr_err("crypto_comp_compress failed, ret = %d!\n", ret);
		return ret;
	}

	return outlen;
}