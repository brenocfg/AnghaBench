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
typedef  int /*<<< orphan*/  PullFilter ;
typedef  int /*<<< orphan*/  PGP_CFB ;

/* Variables and functions */
 int /*<<< orphan*/  pgp_cfb_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pullf_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
decrypt_read(void *priv, PullFilter *src, int len,
			 uint8 **data_p, uint8 *buf, int buflen)
{
	PGP_CFB    *cfb = priv;
	uint8	   *tmp;
	int			res;

	res = pullf_read(src, len, &tmp);
	if (res > 0)
	{
		pgp_cfb_decrypt(cfb, tmp, res, buf);
		*data_p = buf;
	}
	return res;
}