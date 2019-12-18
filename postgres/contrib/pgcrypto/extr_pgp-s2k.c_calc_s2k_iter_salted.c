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
typedef  int /*<<< orphan*/  const uint8 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {unsigned int key_len; int /*<<< orphan*/  const* salt; int /*<<< orphan*/  const* key; int /*<<< orphan*/  iter; } ;
typedef  int /*<<< orphan*/  PX_MD ;
typedef  TYPE_1__ PGP_S2K ;

/* Variables and functions */
 int PGP_MAX_DIGEST ; 
 unsigned int PGP_S2K_SALT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  px_md_finish (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  px_md_reset (int /*<<< orphan*/ *) ; 
 unsigned int px_md_result_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 unsigned int s2k_decode_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
calc_s2k_iter_salted(PGP_S2K *s2k, PX_MD *md, const uint8 *key,
					 unsigned key_len)
{
	unsigned	md_rlen;
	uint8		buf[PGP_MAX_DIGEST];
	uint8	   *dst;
	unsigned	preload = 0;
	unsigned	remain,
				c,
				curcnt,
				count;

	count = s2k_decode_count(s2k->iter);

	md_rlen = px_md_result_size(md);

	remain = s2k->key_len;
	dst = s2k->key;
	while (remain > 0)
	{
		px_md_reset(md);

		if (preload)
		{
			memset(buf, 0, preload);
			px_md_update(md, buf, preload);
		}
		preload++;

		px_md_update(md, s2k->salt, PGP_S2K_SALT);
		px_md_update(md, key, key_len);
		curcnt = PGP_S2K_SALT + key_len;

		while (curcnt < count)
		{
			if (curcnt + PGP_S2K_SALT < count)
				c = PGP_S2K_SALT;
			else
				c = count - curcnt;
			px_md_update(md, s2k->salt, c);
			curcnt += c;

			if (curcnt + key_len < count)
				c = key_len;
			else if (curcnt < count)
				c = count - curcnt;
			else
				break;
			px_md_update(md, key, c);
			curcnt += c;
		}
		px_md_finish(md, buf);

		if (remain > md_rlen)
		{
			memcpy(dst, buf, md_rlen);
			remain -= md_rlen;
			dst += md_rlen;
		}
		else
		{
			memcpy(dst, buf, remain);
			remain = 0;
		}
	}
	px_memset(buf, 0, sizeof(buf));
	return 0;
}