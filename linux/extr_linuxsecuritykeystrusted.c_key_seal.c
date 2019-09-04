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
struct trusted_key_payload {size_t key_len; int /*<<< orphan*/  blob_len; int /*<<< orphan*/  blob; int /*<<< orphan*/ * key; int /*<<< orphan*/  migratable; } ;
struct trusted_key_options {int /*<<< orphan*/  pcrinfo_len; int /*<<< orphan*/  pcrinfo; int /*<<< orphan*/  blobauth; int /*<<< orphan*/  keyauth; int /*<<< orphan*/  keyhandle; int /*<<< orphan*/  keytype; } ;
struct tpm_buf {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tpm_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct tpm_buf*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int tpm_seal (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int key_seal(struct trusted_key_payload *p,
		    struct trusted_key_options *o)
{
	struct tpm_buf *tb;
	int ret;

	tb = kzalloc(sizeof *tb, GFP_KERNEL);
	if (!tb)
		return -ENOMEM;

	/* include migratable flag at end of sealed key */
	p->key[p->key_len] = p->migratable;

	ret = tpm_seal(tb, o->keytype, o->keyhandle, o->keyauth,
		       p->key, p->key_len + 1, p->blob, &p->blob_len,
		       o->blobauth, o->pcrinfo, o->pcrinfo_len);
	if (ret < 0)
		pr_info("trusted_key: srkseal failed (%d)\n", ret);

	kzfree(tb);
	return ret;
}