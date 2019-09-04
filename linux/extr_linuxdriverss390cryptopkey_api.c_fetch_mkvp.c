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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int query_crypto_facility (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,size_t*,char*,size_t*) ; 

__attribute__((used)) static int fetch_mkvp(u16 cardnr, u16 domain, u64 mkvp[2])
{
	int rc, found = 0;
	size_t rlen, vlen;
	u8 *rarray, *varray, *pg;

	pg = (u8 *) __get_free_page(GFP_KERNEL);
	if (!pg)
		return -ENOMEM;
	rarray = pg;
	varray = pg + PAGE_SIZE/2;
	rlen = vlen = PAGE_SIZE/2;

	rc = query_crypto_facility(cardnr, domain, "STATICSA",
				   rarray, &rlen, varray, &vlen);
	if (rc == 0 && rlen > 8*8 && vlen > 184+8) {
		if (rarray[8*8] == '2') {
			/* current master key state is valid */
			mkvp[0] = *((u64 *)(varray + 184));
			mkvp[1] = *((u64 *)(varray + 172));
			found = 1;
		}
	}

	free_page((unsigned long) pg);

	return found ? 0 : -ENOENT;
}