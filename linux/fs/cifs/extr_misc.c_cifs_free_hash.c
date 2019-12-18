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
struct sdesc {int dummy; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int /*<<< orphan*/  kfree (struct sdesc*) ; 

void
cifs_free_hash(struct crypto_shash **shash, struct sdesc **sdesc)
{
	kfree(*sdesc);
	*sdesc = NULL;
	if (*shash)
		crypto_free_shash(*shash);
	*shash = NULL;
}