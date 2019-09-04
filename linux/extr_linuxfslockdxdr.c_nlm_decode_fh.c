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
struct nfs_fh {unsigned int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int NFS2_FHSIZE ; 
 int XDR_QUADLEN (unsigned int) ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *
nlm_decode_fh(__be32 *p, struct nfs_fh *f)
{
	unsigned int	len;

	if ((len = ntohl(*p++)) != NFS2_FHSIZE) {
		dprintk("lockd: bad fhandle size %d (should be %d)\n",
			len, NFS2_FHSIZE);
		return NULL;
	}
	f->size = NFS2_FHSIZE;
	memset(f->data, 0, sizeof(f->data));
	memcpy(f->data, p, NFS2_FHSIZE);
	return p + XDR_QUADLEN(NFS2_FHSIZE);
}