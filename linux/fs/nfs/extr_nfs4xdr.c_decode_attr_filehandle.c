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
typedef  unsigned int uint32_t ;
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
struct nfs_fh {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 unsigned int FATTR4_WORD0_FILEHANDLE ; 
 int NFS4_FHSIZE ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct nfs_fh*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_attr_filehandle(struct xdr_stream *xdr, uint32_t *bitmap, struct nfs_fh *fh)
{
	__be32 *p;
	u32 len;

	if (fh != NULL)
		memset(fh, 0, sizeof(*fh));

	if (unlikely(bitmap[0] & (FATTR4_WORD0_FILEHANDLE - 1U)))
		return -EIO;
	if (likely(bitmap[0] & FATTR4_WORD0_FILEHANDLE)) {
		p = xdr_inline_decode(xdr, 4);
		if (unlikely(!p))
			return -EIO;
		len = be32_to_cpup(p);
		if (len > NFS4_FHSIZE)
			return -EIO;
		p = xdr_inline_decode(xdr, len);
		if (unlikely(!p))
			return -EIO;
		if (fh != NULL) {
			memcpy(fh->data, p, len);
			fh->size = len;
		}
		bitmap[0] &= ~FATTR4_WORD0_FILEHANDLE;
	}
	return 0;
}