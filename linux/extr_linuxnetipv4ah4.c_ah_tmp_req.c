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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ PTR_ALIGN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,struct crypto_ahash*) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static inline struct ahash_request *ah_tmp_req(struct crypto_ahash *ahash,
					       u8 *icv)
{
	struct ahash_request *req;

	req = (void *)PTR_ALIGN(icv + crypto_ahash_digestsize(ahash),
				crypto_tfm_ctx_alignment());

	ahash_request_set_tfm(req, ahash);

	return req;
}