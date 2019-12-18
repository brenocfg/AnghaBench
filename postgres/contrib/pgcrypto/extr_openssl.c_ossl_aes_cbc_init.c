#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_6__ {int klen; int /*<<< orphan*/  evp_ciph; } ;
struct TYPE_5__ {TYPE_2__* ptr; } ;
typedef  TYPE_1__ PX_Cipher ;
typedef  TYPE_2__ OSSLCipher ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_aes_192_cbc () ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int PXE_CIPHER_INIT ; 
 int ossl_aes_init (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ossl_aes_cbc_init(PX_Cipher *c, const uint8 *key, unsigned klen, const uint8 *iv)
{
	OSSLCipher *od = c->ptr;
	int			err;

	err = ossl_aes_init(c, key, klen, iv);
	if (err)
		return err;

	switch (od->klen)
	{
		case 128 / 8:
			od->evp_ciph = EVP_aes_128_cbc();
			break;
		case 192 / 8:
			od->evp_ciph = EVP_aes_192_cbc();
			break;
		case 256 / 8:
			od->evp_ciph = EVP_aes_256_cbc();
			break;
		default:
			/* shouldn't happen */
			err = PXE_CIPHER_INIT;
			break;
	}

	return err;
}