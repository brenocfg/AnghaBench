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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS3_COOKIEVERFSIZE ; 
 int XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *xdr_encode_cookieverf3(__be32 *p, const __be32 *verifier)
{
	memcpy(p, verifier, NFS3_COOKIEVERFSIZE);
	return p + XDR_QUADLEN(NFS3_COOKIEVERFSIZE);
}