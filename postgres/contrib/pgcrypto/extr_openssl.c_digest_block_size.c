#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
typedef  TYPE_2__ PX_MD ;
typedef  TYPE_3__ OSSLDigest ;

/* Variables and functions */
 int EVP_MD_CTX_block_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
digest_block_size(PX_MD *h)
{
	OSSLDigest *digest = (OSSLDigest *) h->p.ptr;

	return EVP_MD_CTX_block_size(digest->ctx);
}