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
struct TYPE_5__ {scalar_t__ ptr; } ;
struct TYPE_6__ {TYPE_1__ p; } ;
typedef  TYPE_2__ PX_MD ;
typedef  int /*<<< orphan*/  OSSLDigest ;

/* Variables and functions */
 int /*<<< orphan*/  free_openssl_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_free (TYPE_2__*) ; 

__attribute__((used)) static void
digest_free(PX_MD *h)
{
	OSSLDigest *digest = (OSSLDigest *) h->p.ptr;

	free_openssl_digest(digest);
	px_free(h);
}