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
struct scatterlist {int dummy; } ;
struct iov_iter {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 size_t copy_to_iter (void const*,size_t,struct iov_iter*) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void const*,size_t) ; 

size_t hash_and_copy_to_iter(const void *addr, size_t bytes, void *hashp,
		struct iov_iter *i)
{
#ifdef CONFIG_CRYPTO
	struct ahash_request *hash = hashp;
	struct scatterlist sg;
	size_t copied;

	copied = copy_to_iter(addr, bytes, i);
	sg_init_one(&sg, addr, copied);
	ahash_request_set_crypt(hash, &sg, NULL, copied);
	crypto_ahash_update(hash);
	return copied;
#else
	return 0;
#endif
}