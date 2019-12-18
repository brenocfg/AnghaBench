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
typedef  scalar_t__ u8 ;
struct z_erofs_maprecorder {int clusterofs; unsigned int* delta; scalar_t__ pblk; scalar_t__ type; scalar_t__* kaddr; int /*<<< orphan*/  inode; } ;
struct erofs_inode {unsigned int z_logical_clusterbits; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct erofs_inode* EROFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD ; 
 unsigned int decode_compactedbits (unsigned int const,unsigned int const,scalar_t__*,unsigned int,scalar_t__*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int round_down (unsigned int,unsigned int) ; 

__attribute__((used)) static int unpack_compacted_index(struct z_erofs_maprecorder *m,
				  unsigned int amortizedshift,
				  unsigned int eofs)
{
	struct erofs_inode *const vi = EROFS_I(m->inode);
	const unsigned int lclusterbits = vi->z_logical_clusterbits;
	const unsigned int lomask = (1 << lclusterbits) - 1;
	unsigned int vcnt, base, lo, encodebits, nblk;
	int i;
	u8 *in, type;

	if (1 << amortizedshift == 4)
		vcnt = 2;
	else if (1 << amortizedshift == 2 && lclusterbits == 12)
		vcnt = 16;
	else
		return -EOPNOTSUPP;

	encodebits = ((vcnt << amortizedshift) - sizeof(__le32)) * 8 / vcnt;
	base = round_down(eofs, vcnt << amortizedshift);
	in = m->kaddr + base;

	i = (eofs - base) >> amortizedshift;

	lo = decode_compactedbits(lclusterbits, lomask,
				  in, encodebits * i, &type);
	m->type = type;
	if (type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD) {
		m->clusterofs = 1 << lclusterbits;
		if (i + 1 != vcnt) {
			m->delta[0] = lo;
			return 0;
		}
		/*
		 * since the last lcluster in the pack is special,
		 * of which lo saves delta[1] rather than delta[0].
		 * Hence, get delta[0] by the previous lcluster indirectly.
		 */
		lo = decode_compactedbits(lclusterbits, lomask,
					  in, encodebits * (i - 1), &type);
		if (type != Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD)
			lo = 0;
		m->delta[0] = lo + 1;
		return 0;
	}
	m->clusterofs = lo;
	m->delta[0] = 0;
	/* figout out blkaddr (pblk) for HEAD lclusters */
	nblk = 1;
	while (i > 0) {
		--i;
		lo = decode_compactedbits(lclusterbits, lomask,
					  in, encodebits * i, &type);
		if (type == Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD)
			i -= lo;

		if (i >= 0)
			++nblk;
	}
	in += (vcnt << amortizedshift) - sizeof(__le32);
	m->pblk = le32_to_cpu(*(__le32 *)in) + nblk;
	return 0;
}