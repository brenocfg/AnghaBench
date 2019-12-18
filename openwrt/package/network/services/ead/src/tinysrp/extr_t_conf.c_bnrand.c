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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t_random (unsigned char*,int) ; 

__attribute__((used)) static int bnrand(int pseudorand, BIGNUM *rnd, int bits, int top, int bottom)
	{
	unsigned char *buf=NULL;
	int ret=0,bit,bytes,mask;

	if (bits == 0)
		{
		BN_zero(rnd);
		return 1;
		}

	bytes=(bits+7)/8;
	bit=(bits-1)%8;
	mask=0xff<<bit;

	buf=(unsigned char *)malloc(bytes);
	if (buf == NULL)
		{
		goto err;
		}

	/* make a random number and set the top and bottom bits */
	/* this ignores the pseudorand flag */

	t_random(buf, bytes);

	if (top)
		{
		if (bit == 0)
			{
			buf[0]=1;
			buf[1]|=0x80;
			}
		else
			{
			buf[0]|=(3<<(bit-1));
			buf[0]&= ~(mask<<1);
			}
		}
	else
		{
		buf[0]|=(1<<bit);
		buf[0]&= ~(mask<<1);
		}
	if (bottom) /* set bottom bits to whatever odd is */
		buf[bytes-1]|=1;
	if (!BN_bin2bn(buf,bytes,rnd)) goto err;
	ret=1;
err:
	if (buf != NULL)
		{
		memset(buf,0,bytes);
		free(buf);
		}
	return(ret);
	}