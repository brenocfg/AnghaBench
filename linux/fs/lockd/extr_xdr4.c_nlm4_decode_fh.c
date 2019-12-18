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
struct nfs_fh {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS_MAXFHSIZE ; 
 int XDR_QUADLEN (scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *
nlm4_decode_fh(__be32 *p, struct nfs_fh *f)
{
	memset(f->data, 0, sizeof(f->data));
	f->size = ntohl(*p++);
	if (f->size > NFS_MAXFHSIZE) {
		dprintk("lockd: bad fhandle size %d (should be <=%d)\n",
			f->size, NFS_MAXFHSIZE);
		return NULL;
	}
      	memcpy(f->data, p, f->size);
	return p + XDR_QUADLEN(f->size);
}