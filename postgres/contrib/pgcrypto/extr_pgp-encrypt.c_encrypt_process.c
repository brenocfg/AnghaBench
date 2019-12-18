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
typedef  int /*<<< orphan*/  uint8 ;
struct EncStat {int /*<<< orphan*/  buf; int /*<<< orphan*/  ciph; } ;
typedef  int /*<<< orphan*/  PushFilter ;

/* Variables and functions */
 int ENCBUF ; 
 int pgp_cfb_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
encrypt_process(PushFilter *next, void *priv, const uint8 *data, int len)
{
	int			res;
	struct EncStat *st = priv;
	int			avail = len;

	while (avail > 0)
	{
		int			tmplen = avail > ENCBUF ? ENCBUF : avail;

		res = pgp_cfb_encrypt(st->ciph, data, tmplen, st->buf);
		if (res < 0)
			return res;

		res = pushf_write(next, st->buf, tmplen);
		if (res < 0)
			return res;

		data += tmplen;
		avail -= tmplen;
	}
	return 0;
}