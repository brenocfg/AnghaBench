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
struct net_device {int dummy; } ;
struct dscc4_dev_priv {unsigned short encoding; unsigned short parity; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short ENCODING_FM_MARK ; 
 unsigned short ENCODING_FM_SPACE ; 
 unsigned short ENCODING_MANCHESTER ; 
 unsigned short ENCODING_NRZ ; 
 unsigned short ENCODING_NRZI ; 
 unsigned short PARITY_CRC16_PR0_CCITT ; 
 unsigned short PARITY_CRC16_PR1_CCITT ; 
 unsigned short PARITY_CRC32_PR0_CCITT ; 
 unsigned short PARITY_CRC32_PR1_CCITT ; 
 unsigned short PARITY_NONE ; 
 struct dscc4_dev_priv* dscc4_priv (struct net_device*) ; 

__attribute__((used)) static int dscc4_hdlc_attach(struct net_device *dev, unsigned short encoding,
	unsigned short parity)
{
	struct dscc4_dev_priv *dpriv = dscc4_priv(dev);

	if (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI &&
	    encoding != ENCODING_FM_MARK &&
	    encoding != ENCODING_FM_SPACE &&
	    encoding != ENCODING_MANCHESTER)
		return -EINVAL;

	if (parity != PARITY_NONE &&
	    parity != PARITY_CRC16_PR0_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT &&
	    parity != PARITY_CRC32_PR0_CCITT &&
	    parity != PARITY_CRC32_PR1_CCITT)
		return -EINVAL;

        dpriv->encoding = encoding;
        dpriv->parity = parity;
	return 0;
}