#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tfm; } ;
struct kdf_sdesc {TYPE_1__ shash; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 int /*<<< orphan*/  kzfree (struct kdf_sdesc*) ; 

__attribute__((used)) static void kdf_dealloc(struct kdf_sdesc *sdesc)
{
	if (!sdesc)
		return;

	if (sdesc->shash.tfm)
		crypto_free_shash(sdesc->shash.tfm);

	kzfree(sdesc);
}