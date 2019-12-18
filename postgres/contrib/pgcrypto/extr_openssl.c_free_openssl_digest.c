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
struct TYPE_7__ {TYPE_1__* prev; TYPE_4__* next; int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {TYPE_4__* next; } ;
typedef  TYPE_2__ OSSLDigest ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ ) ; 
 TYPE_4__* open_digests ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static void
free_openssl_digest(OSSLDigest *digest)
{
	EVP_MD_CTX_destroy(digest->ctx);
	if (digest->prev)
		digest->prev->next = digest->next;
	else
		open_digests = digest->next;
	if (digest->next)
		digest->next->prev = digest->prev;
	pfree(digest);
}