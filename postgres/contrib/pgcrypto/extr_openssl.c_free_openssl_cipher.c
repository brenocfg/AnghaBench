#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_1__* prev; TYPE_4__* next; int /*<<< orphan*/  evp_ctx; } ;
struct TYPE_6__ {TYPE_4__* next; } ;
typedef  TYPE_2__ OSSLCipher ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ ) ; 
 TYPE_4__* open_ciphers ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
free_openssl_cipher(OSSLCipher *od)
{
	EVP_CIPHER_CTX_free(od->evp_ctx);
	if (od->prev)
		od->prev->next = od->next;
	else
		open_ciphers = od->next;
	if (od->next)
		od->next->prev = od->prev;
	pfree(od);
}