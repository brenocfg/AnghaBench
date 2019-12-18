#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  GistInetKey ;
typedef  TYPE_1__ GISTENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetInetKeyP (int /*<<< orphan*/ ) ; 
 int bitncommon (unsigned char*,unsigned char*,int) ; 
 unsigned char* gk_ip_addr (int /*<<< orphan*/ *) ; 
 int gk_ip_commonbits (int /*<<< orphan*/ *) ; 
 int gk_ip_family (int /*<<< orphan*/ *) ; 
 int gk_ip_minbits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
calc_inet_union_params(GISTENTRY *ent,
					   int m, int n,
					   int *minfamily_p,
					   int *maxfamily_p,
					   int *minbits_p,
					   int *commonbits_p)
{
	int			minfamily,
				maxfamily,
				minbits,
				commonbits;
	unsigned char *addr;
	GistInetKey *tmp;
	int			i;

	/* Must be at least one key. */
	Assert(m <= n);

	/* Initialize variables using the first key. */
	tmp = DatumGetInetKeyP(ent[m].key);
	minfamily = maxfamily = gk_ip_family(tmp);
	minbits = gk_ip_minbits(tmp);
	commonbits = gk_ip_commonbits(tmp);
	addr = gk_ip_addr(tmp);

	/* Scan remaining keys. */
	for (i = m + 1; i <= n; i++)
	{
		tmp = DatumGetInetKeyP(ent[i].key);

		/* Determine range of family numbers */
		if (minfamily > gk_ip_family(tmp))
			minfamily = gk_ip_family(tmp);
		if (maxfamily < gk_ip_family(tmp))
			maxfamily = gk_ip_family(tmp);

		/* Find minimum minbits */
		if (minbits > gk_ip_minbits(tmp))
			minbits = gk_ip_minbits(tmp);

		/* Find minimum number of bits in common */
		if (commonbits > gk_ip_commonbits(tmp))
			commonbits = gk_ip_commonbits(tmp);
		if (commonbits > 0)
			commonbits = bitncommon(addr, gk_ip_addr(tmp), commonbits);
	}

	/* Force minbits/commonbits to zero if more than one family. */
	if (minfamily != maxfamily)
		minbits = commonbits = 0;

	*minfamily_p = minfamily;
	*maxfamily_p = maxfamily;
	*minbits_p = minbits;
	*commonbits_p = commonbits;
}