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
typedef  int u8 ;
struct atp_unit {unsigned short* host_id; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;

/* Variables and functions */
 int atp_readb_io (struct atp_unit*,int /*<<< orphan*/ ,int) ; 
 int atp_readw_io (struct atp_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atp_writeb_io (struct atp_unit*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  atp_writew_io (struct atp_unit*,int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned char fun_scam (struct atp_unit*,unsigned short*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tscam(struct Scsi_Host *host, bool wide_chip, u8 scam_on)
{

	unsigned char i, j, k;
	unsigned long n;
	unsigned short int m, assignid_map, val;
	unsigned char mbuf[33], quintet[2];
	struct atp_unit *dev = (struct atp_unit *)&host->hostdata;
	static unsigned char g2q_tab[8] = {
		0x38, 0x31, 0x32, 0x2b, 0x34, 0x2d, 0x2e, 0x27
	};

/*  I can't believe we need this before we've even done anything.  Remove it
 *  and see if anyone bitches.
	for (i = 0; i < 0x10; i++) {
		udelay(0xffff);
	}
 */

	atp_writeb_io(dev, 0, 1, 0x08);
	atp_writeb_io(dev, 0, 2, 0x7f);
	atp_writeb_io(dev, 0, 0x11, 0x20);

	if ((scam_on & 0x40) == 0) {
		return;
	}
	m = 1;
	m <<= dev->host_id[0];
	j = 16;
	if (!wide_chip) {
		m |= 0xff00;
		j = 8;
	}
	assignid_map = m;
	atp_writeb_io(dev, 0, 0x02, 0x02);	/* 2*2=4ms,3EH 2/32*3E=3.9ms */
	atp_writeb_io(dev, 0, 0x03, 0);
	atp_writeb_io(dev, 0, 0x04, 0);
	atp_writeb_io(dev, 0, 0x05, 0);
	atp_writeb_io(dev, 0, 0x06, 0);
	atp_writeb_io(dev, 0, 0x07, 0);
	atp_writeb_io(dev, 0, 0x08, 0);

	for (i = 0; i < j; i++) {
		m = 1;
		m = m << i;
		if ((m & assignid_map) != 0) {
			continue;
		}
		atp_writeb_io(dev, 0, 0x0f, 0);
		atp_writeb_io(dev, 0, 0x12, 0);
		atp_writeb_io(dev, 0, 0x13, 0);
		atp_writeb_io(dev, 0, 0x14, 0);
		if (i > 7) {
			k = (i & 0x07) | 0x40;
		} else {
			k = i;
		}
		atp_writeb_io(dev, 0, 0x15, k);
		if (wide_chip)
			atp_writeb_io(dev, 0, 0x1b, 0x01);
		else
			atp_writeb_io(dev, 0, 0x1b, 0x00);
		do {
			atp_writeb_io(dev, 0, 0x18, 0x09);

			while ((atp_readb_io(dev, 0, 0x1f) & 0x80) == 0x00)
				cpu_relax();
			k = atp_readb_io(dev, 0, 0x17);
			if ((k == 0x85) || (k == 0x42))
				break;
			if (k != 0x16)
				atp_writeb_io(dev, 0, 0x10, 0x41);
		} while (k != 0x16);
		if ((k == 0x85) || (k == 0x42))
			continue;
		assignid_map |= m;

	}
	atp_writeb_io(dev, 0, 0x02, 0x7f);
	atp_writeb_io(dev, 0, 0x1b, 0x02);

	udelay(2);

	val = 0x0080;		/* bsy  */
	atp_writew_io(dev, 0, 0x1c, val);
	val |= 0x0040;		/* sel  */
	atp_writew_io(dev, 0, 0x1c, val);
	val |= 0x0004;		/* msg  */
	atp_writew_io(dev, 0, 0x1c, val);
	udelay(2);		/* 2 deskew delay(45ns*2=90ns) */
	val &= 0x007f;		/* no bsy  */
	atp_writew_io(dev, 0, 0x1c, val);
	msleep(128);
	val &= 0x00fb;		/* after 1ms no msg */
	atp_writew_io(dev, 0, 0x1c, val);
	while ((atp_readb_io(dev, 0, 0x1c) & 0x04) != 0)
		;
	udelay(2);
	udelay(100);
	for (n = 0; n < 0x30000; n++)
		if ((atp_readb_io(dev, 0, 0x1c) & 0x80) != 0)	/* bsy ? */
			break;
	if (n < 0x30000)
		for (n = 0; n < 0x30000; n++)
			if ((atp_readb_io(dev, 0, 0x1c) & 0x81) == 0x0081) {
				udelay(2);
				val |= 0x8003;		/* io,cd,db7  */
				atp_writew_io(dev, 0, 0x1c, val);
				udelay(2);
				val &= 0x00bf;		/* no sel     */
				atp_writew_io(dev, 0, 0x1c, val);
				udelay(2);
				break;
			}
	while (1) {
	/*
	 * The funny division into multiple delays is to accomodate
	 * arches like ARM where udelay() multiplies its argument by
	 * a large number to initialize a loop counter.  To avoid
	 * overflow, the maximum supported udelay is 2000 microseconds.
	 *
	 * XXX it would be more polite to find a way to use msleep()
	 */
	mdelay(2);
	udelay(48);
	if ((atp_readb_io(dev, 0, 0x1c) & 0x80) == 0x00) {	/* bsy ? */
		atp_writew_io(dev, 0, 0x1c, 0);
		atp_writeb_io(dev, 0, 0x1b, 0);
		atp_writeb_io(dev, 0, 0x15, 0);
		atp_writeb_io(dev, 0, 0x18, 0x09);
		while ((atp_readb_io(dev, 0, 0x1f) & 0x80) == 0)
			cpu_relax();
		atp_readb_io(dev, 0, 0x17);
		return;
	}
	val &= 0x00ff;		/* synchronization  */
	val |= 0x3f00;
	fun_scam(dev, &val);
	udelay(2);
	val &= 0x00ff;		/* isolation        */
	val |= 0x2000;
	fun_scam(dev, &val);
	udelay(2);
	i = 8;
	j = 0;

	while (1) {
		if ((atp_readw_io(dev, 0, 0x1c) & 0x2000) == 0)
			continue;
		udelay(2);
		val &= 0x00ff;		/* get ID_STRING */
		val |= 0x2000;
		k = fun_scam(dev, &val);
		if ((k & 0x03) == 0)
			break;
		mbuf[j] <<= 0x01;
		mbuf[j] &= 0xfe;
		if ((k & 0x02) != 0)
			mbuf[j] |= 0x01;
		i--;
		if (i > 0)
			continue;
		j++;
		i = 8;
	}

	/* isolation complete..  */
/*    mbuf[32]=0;
	printk(" \n%x %x %x %s\n ",assignid_map,mbuf[0],mbuf[1],&mbuf[2]); */
	i = 15;
	j = mbuf[0];
	if ((j & 0x20) != 0) {	/* bit5=1:ID up to 7      */
		i = 7;
	}
	if ((j & 0x06) != 0) {	/* IDvalid?             */
		k = mbuf[1];
		while (1) {
			m = 1;
			m <<= k;
			if ((m & assignid_map) == 0)
				break;
			if (k > 0)
				k--;
			else
				break;
		}
	}
	if ((m & assignid_map) != 0) {	/* srch from max acceptable ID#  */
		k = i;			/* max acceptable ID#            */
		while (1) {
			m = 1;
			m <<= k;
			if ((m & assignid_map) == 0)
				break;
			if (k > 0)
				k--;
			else
				break;
		}
	}
	/* k=binID#,       */
	assignid_map |= m;
	if (k < 8) {
		quintet[0] = 0x38;	/* 1st dft ID<8    */
	} else {
		quintet[0] = 0x31;	/* 1st  ID>=8      */
	}
	k &= 0x07;
	quintet[1] = g2q_tab[k];

	val &= 0x00ff;		/* AssignID 1stQuintet,AH=001xxxxx  */
	m = quintet[0] << 8;
	val |= m;
	fun_scam(dev, &val);
	val &= 0x00ff;		/* AssignID 2ndQuintet,AH=001xxxxx */
	m = quintet[1] << 8;
	val |= m;
	fun_scam(dev, &val);

	}
}