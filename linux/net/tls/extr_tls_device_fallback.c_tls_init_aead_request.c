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
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_AAD_SPACE_SIZE ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 

__attribute__((used)) static void tls_init_aead_request(struct aead_request *aead_req,
				  struct crypto_aead *aead)
{
	aead_request_set_tfm(aead_req, aead);
	aead_request_set_ad(aead_req, TLS_AAD_SPACE_SIZE);
}