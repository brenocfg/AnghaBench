#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ tfm; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  apparmor_hash_size ; 
 scalar_t__ apparmor_tfm ; 
 int crypto_shash_final (TYPE_1__*,char*) ; 
 int crypto_shash_init (TYPE_1__*) ; 
 int crypto_shash_update (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *aa_calc_hash(void *data, size_t len)
{
	SHASH_DESC_ON_STACK(desc, apparmor_tfm);
	char *hash = NULL;
	int error = -ENOMEM;

	if (!apparmor_tfm)
		return NULL;

	hash = kzalloc(apparmor_hash_size, GFP_KERNEL);
	if (!hash)
		goto fail;

	desc->tfm = apparmor_tfm;

	error = crypto_shash_init(desc);
	if (error)
		goto fail;
	error = crypto_shash_update(desc, (u8 *) data, len);
	if (error)
		goto fail;
	error = crypto_shash_final(desc, hash);
	if (error)
		goto fail;

	return hash;

fail:
	kfree(hash);

	return ERR_PTR(error);
}