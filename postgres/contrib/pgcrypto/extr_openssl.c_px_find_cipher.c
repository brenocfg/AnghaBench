#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ossl_cipher_lookup {TYPE_1__* ciph; int /*<<< orphan*/ * name; } ;
struct TYPE_11__ {TYPE_1__* ciph; int /*<<< orphan*/  evp_ciph; int /*<<< orphan*/ * prev; struct TYPE_11__* next; int /*<<< orphan*/  owner; int /*<<< orphan*/ * evp_ctx; } ;
struct TYPE_10__ {TYPE_3__* ptr; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  init; int /*<<< orphan*/  free; int /*<<< orphan*/  iv_size; int /*<<< orphan*/  key_size; int /*<<< orphan*/  block_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  init; int /*<<< orphan*/  (* cipher_func ) () ;} ;
typedef  TYPE_2__ PX_Cipher ;
typedef  TYPE_3__ OSSLCipher ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 TYPE_3__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int PXE_CIPHER_INIT ; 
 int PXE_NO_CIPHER ; 
 int /*<<< orphan*/  RegisterResourceReleaseCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  cipher_free_callback ; 
 int cipher_resowner_callback_registered ; 
 int /*<<< orphan*/  gen_ossl_block_size ; 
 int /*<<< orphan*/  gen_ossl_decrypt ; 
 int /*<<< orphan*/  gen_ossl_encrypt ; 
 int /*<<< orphan*/  gen_ossl_free ; 
 int /*<<< orphan*/  gen_ossl_iv_size ; 
 int /*<<< orphan*/  gen_ossl_key_size ; 
 TYPE_3__* open_ciphers ; 
 int /*<<< orphan*/  ossl_aliases ; 
 struct ossl_cipher_lookup* ossl_cipher_types ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 TYPE_2__* px_alloc (int) ; 
 char* px_resolve_alias (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub1 () ; 

int
px_find_cipher(const char *name, PX_Cipher **res)
{
	const struct ossl_cipher_lookup *i;
	PX_Cipher  *c = NULL;
	EVP_CIPHER_CTX *ctx;
	OSSLCipher *od;

	name = px_resolve_alias(ossl_aliases, name);
	for (i = ossl_cipher_types; i->name; i++)
		if (strcmp(i->name, name) == 0)
			break;
	if (i->name == NULL)
		return PXE_NO_CIPHER;

	if (!cipher_resowner_callback_registered)
	{
		RegisterResourceReleaseCallback(cipher_free_callback, NULL);
		cipher_resowner_callback_registered = true;
	}

	/*
	 * Create an OSSLCipher object, an EVP_CIPHER_CTX object and a PX_Cipher.
	 * The order is crucial, to make sure we don't leak anything on
	 * out-of-memory or other error.
	 */
	od = MemoryContextAllocZero(TopMemoryContext, sizeof(*od));
	od->ciph = i->ciph;

	/* Allocate an EVP_CIPHER_CTX object. */
	ctx = EVP_CIPHER_CTX_new();
	if (!ctx)
	{
		pfree(od);
		return PXE_CIPHER_INIT;
	}

	od->evp_ctx = ctx;
	od->owner = CurrentResourceOwner;
	od->next = open_ciphers;
	od->prev = NULL;
	open_ciphers = od;

	if (i->ciph->cipher_func)
		od->evp_ciph = i->ciph->cipher_func();

	/* The PX_Cipher is allocated in current memory context */
	c = px_alloc(sizeof(*c));
	c->block_size = gen_ossl_block_size;
	c->key_size = gen_ossl_key_size;
	c->iv_size = gen_ossl_iv_size;
	c->free = gen_ossl_free;
	c->init = od->ciph->init;
	c->encrypt = gen_ossl_encrypt;
	c->decrypt = gen_ossl_decrypt;
	c->ptr = od;

	*res = c;
	return 0;
}