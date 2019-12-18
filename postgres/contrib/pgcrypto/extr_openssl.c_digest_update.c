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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_7__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {scalar_t__ ptr; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
typedef  TYPE_2__ PX_MD ;
typedef  TYPE_3__ OSSLDigest ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void
digest_update(PX_MD *h, const uint8 *data, unsigned dlen)
{
	OSSLDigest *digest = (OSSLDigest *) h->p.ptr;

	EVP_DigestUpdate(digest->ctx, data, dlen);
}