#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int rx_chain_num; } ;
struct rt2x00_dev {TYPE_1__ default_ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP105_MLD ; 
 int /*<<< orphan*/  rt2800_bbp4_mac_if_ctrl (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_bbp_dcoc_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_bbp_glrt_write (struct rt2x00_dev*,int,int) ; 
 int rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_init_bbp_6352(struct rt2x00_dev *rt2x00dev)
{
	u8 bbp;

	/* Apply Maximum Likelihood Detection (MLD) for 2 stream case */
	bbp = rt2800_bbp_read(rt2x00dev, 105);
	rt2x00_set_field8(&bbp, BBP105_MLD,
			  rt2x00dev->default_ant.rx_chain_num == 2);
	rt2800_bbp_write(rt2x00dev, 105, bbp);

	/* Avoid data loss and CRC errors */
	rt2800_bbp4_mac_if_ctrl(rt2x00dev);

	/* Fix I/Q swap issue */
	bbp = rt2800_bbp_read(rt2x00dev, 1);
	bbp |= 0x04;
	rt2800_bbp_write(rt2x00dev, 1, bbp);

	/* BBP for G band */
	rt2800_bbp_write(rt2x00dev, 3, 0x08);
	rt2800_bbp_write(rt2x00dev, 4, 0x00); /* rt2800_bbp4_mac_if_ctrl? */
	rt2800_bbp_write(rt2x00dev, 6, 0x08);
	rt2800_bbp_write(rt2x00dev, 14, 0x09);
	rt2800_bbp_write(rt2x00dev, 15, 0xFF);
	rt2800_bbp_write(rt2x00dev, 16, 0x01);
	rt2800_bbp_write(rt2x00dev, 20, 0x06);
	rt2800_bbp_write(rt2x00dev, 21, 0x00);
	rt2800_bbp_write(rt2x00dev, 22, 0x00);
	rt2800_bbp_write(rt2x00dev, 27, 0x00);
	rt2800_bbp_write(rt2x00dev, 28, 0x00);
	rt2800_bbp_write(rt2x00dev, 30, 0x00);
	rt2800_bbp_write(rt2x00dev, 31, 0x48);
	rt2800_bbp_write(rt2x00dev, 47, 0x40);
	rt2800_bbp_write(rt2x00dev, 62, 0x00);
	rt2800_bbp_write(rt2x00dev, 63, 0x00);
	rt2800_bbp_write(rt2x00dev, 64, 0x00);
	rt2800_bbp_write(rt2x00dev, 65, 0x2C);
	rt2800_bbp_write(rt2x00dev, 66, 0x1C);
	rt2800_bbp_write(rt2x00dev, 67, 0x20);
	rt2800_bbp_write(rt2x00dev, 68, 0xDD);
	rt2800_bbp_write(rt2x00dev, 69, 0x10);
	rt2800_bbp_write(rt2x00dev, 70, 0x05);
	rt2800_bbp_write(rt2x00dev, 73, 0x18);
	rt2800_bbp_write(rt2x00dev, 74, 0x0F);
	rt2800_bbp_write(rt2x00dev, 75, 0x60);
	rt2800_bbp_write(rt2x00dev, 76, 0x44);
	rt2800_bbp_write(rt2x00dev, 77, 0x59);
	rt2800_bbp_write(rt2x00dev, 78, 0x1E);
	rt2800_bbp_write(rt2x00dev, 79, 0x1C);
	rt2800_bbp_write(rt2x00dev, 80, 0x0C);
	rt2800_bbp_write(rt2x00dev, 81, 0x3A);
	rt2800_bbp_write(rt2x00dev, 82, 0xB6);
	rt2800_bbp_write(rt2x00dev, 83, 0x9A);
	rt2800_bbp_write(rt2x00dev, 84, 0x9A);
	rt2800_bbp_write(rt2x00dev, 86, 0x38);
	rt2800_bbp_write(rt2x00dev, 88, 0x90);
	rt2800_bbp_write(rt2x00dev, 91, 0x04);
	rt2800_bbp_write(rt2x00dev, 92, 0x02);
	rt2800_bbp_write(rt2x00dev, 95, 0x9A);
	rt2800_bbp_write(rt2x00dev, 96, 0x00);
	rt2800_bbp_write(rt2x00dev, 103, 0xC0);
	rt2800_bbp_write(rt2x00dev, 104, 0x92);
	/* FIXME BBP105 owerwrite */
	rt2800_bbp_write(rt2x00dev, 105, 0x3C);
	rt2800_bbp_write(rt2x00dev, 106, 0x12);
	rt2800_bbp_write(rt2x00dev, 109, 0x00);
	rt2800_bbp_write(rt2x00dev, 134, 0x10);
	rt2800_bbp_write(rt2x00dev, 135, 0xA6);
	rt2800_bbp_write(rt2x00dev, 137, 0x04);
	rt2800_bbp_write(rt2x00dev, 142, 0x30);
	rt2800_bbp_write(rt2x00dev, 143, 0xF7);
	rt2800_bbp_write(rt2x00dev, 160, 0xEC);
	rt2800_bbp_write(rt2x00dev, 161, 0xC4);
	rt2800_bbp_write(rt2x00dev, 162, 0x77);
	rt2800_bbp_write(rt2x00dev, 163, 0xF9);
	rt2800_bbp_write(rt2x00dev, 164, 0x00);
	rt2800_bbp_write(rt2x00dev, 165, 0x00);
	rt2800_bbp_write(rt2x00dev, 186, 0x00);
	rt2800_bbp_write(rt2x00dev, 187, 0x00);
	rt2800_bbp_write(rt2x00dev, 188, 0x00);
	rt2800_bbp_write(rt2x00dev, 186, 0x00);
	rt2800_bbp_write(rt2x00dev, 187, 0x01);
	rt2800_bbp_write(rt2x00dev, 188, 0x00);
	rt2800_bbp_write(rt2x00dev, 189, 0x00);

	rt2800_bbp_write(rt2x00dev, 91, 0x06);
	rt2800_bbp_write(rt2x00dev, 92, 0x04);
	rt2800_bbp_write(rt2x00dev, 93, 0x54);
	rt2800_bbp_write(rt2x00dev, 99, 0x50);
	rt2800_bbp_write(rt2x00dev, 148, 0x84);
	rt2800_bbp_write(rt2x00dev, 167, 0x80);
	rt2800_bbp_write(rt2x00dev, 178, 0xFF);
	rt2800_bbp_write(rt2x00dev, 106, 0x13);

	/* BBP for G band GLRT function (BBP_128 ~ BBP_221) */
	rt2800_bbp_glrt_write(rt2x00dev, 0, 0x00);
	rt2800_bbp_glrt_write(rt2x00dev, 1, 0x14);
	rt2800_bbp_glrt_write(rt2x00dev, 2, 0x20);
	rt2800_bbp_glrt_write(rt2x00dev, 3, 0x0A);
	rt2800_bbp_glrt_write(rt2x00dev, 10, 0x16);
	rt2800_bbp_glrt_write(rt2x00dev, 11, 0x06);
	rt2800_bbp_glrt_write(rt2x00dev, 12, 0x02);
	rt2800_bbp_glrt_write(rt2x00dev, 13, 0x07);
	rt2800_bbp_glrt_write(rt2x00dev, 14, 0x05);
	rt2800_bbp_glrt_write(rt2x00dev, 15, 0x09);
	rt2800_bbp_glrt_write(rt2x00dev, 16, 0x20);
	rt2800_bbp_glrt_write(rt2x00dev, 17, 0x08);
	rt2800_bbp_glrt_write(rt2x00dev, 18, 0x4A);
	rt2800_bbp_glrt_write(rt2x00dev, 19, 0x00);
	rt2800_bbp_glrt_write(rt2x00dev, 20, 0x00);
	rt2800_bbp_glrt_write(rt2x00dev, 128, 0xE0);
	rt2800_bbp_glrt_write(rt2x00dev, 129, 0x1F);
	rt2800_bbp_glrt_write(rt2x00dev, 130, 0x4F);
	rt2800_bbp_glrt_write(rt2x00dev, 131, 0x32);
	rt2800_bbp_glrt_write(rt2x00dev, 132, 0x08);
	rt2800_bbp_glrt_write(rt2x00dev, 133, 0x28);
	rt2800_bbp_glrt_write(rt2x00dev, 134, 0x19);
	rt2800_bbp_glrt_write(rt2x00dev, 135, 0x0A);
	rt2800_bbp_glrt_write(rt2x00dev, 138, 0x16);
	rt2800_bbp_glrt_write(rt2x00dev, 139, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 140, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 141, 0x1A);
	rt2800_bbp_glrt_write(rt2x00dev, 142, 0x36);
	rt2800_bbp_glrt_write(rt2x00dev, 143, 0x2C);
	rt2800_bbp_glrt_write(rt2x00dev, 144, 0x26);
	rt2800_bbp_glrt_write(rt2x00dev, 145, 0x24);
	rt2800_bbp_glrt_write(rt2x00dev, 146, 0x42);
	rt2800_bbp_glrt_write(rt2x00dev, 147, 0x40);
	rt2800_bbp_glrt_write(rt2x00dev, 148, 0x30);
	rt2800_bbp_glrt_write(rt2x00dev, 149, 0x29);
	rt2800_bbp_glrt_write(rt2x00dev, 150, 0x4C);
	rt2800_bbp_glrt_write(rt2x00dev, 151, 0x46);
	rt2800_bbp_glrt_write(rt2x00dev, 152, 0x3D);
	rt2800_bbp_glrt_write(rt2x00dev, 153, 0x40);
	rt2800_bbp_glrt_write(rt2x00dev, 154, 0x3E);
	rt2800_bbp_glrt_write(rt2x00dev, 155, 0x38);
	rt2800_bbp_glrt_write(rt2x00dev, 156, 0x3D);
	rt2800_bbp_glrt_write(rt2x00dev, 157, 0x2F);
	rt2800_bbp_glrt_write(rt2x00dev, 158, 0x3C);
	rt2800_bbp_glrt_write(rt2x00dev, 159, 0x34);
	rt2800_bbp_glrt_write(rt2x00dev, 160, 0x2C);
	rt2800_bbp_glrt_write(rt2x00dev, 161, 0x2F);
	rt2800_bbp_glrt_write(rt2x00dev, 162, 0x3C);
	rt2800_bbp_glrt_write(rt2x00dev, 163, 0x35);
	rt2800_bbp_glrt_write(rt2x00dev, 164, 0x2E);
	rt2800_bbp_glrt_write(rt2x00dev, 165, 0x2F);
	rt2800_bbp_glrt_write(rt2x00dev, 166, 0x49);
	rt2800_bbp_glrt_write(rt2x00dev, 167, 0x41);
	rt2800_bbp_glrt_write(rt2x00dev, 168, 0x36);
	rt2800_bbp_glrt_write(rt2x00dev, 169, 0x39);
	rt2800_bbp_glrt_write(rt2x00dev, 170, 0x30);
	rt2800_bbp_glrt_write(rt2x00dev, 171, 0x30);
	rt2800_bbp_glrt_write(rt2x00dev, 172, 0x0E);
	rt2800_bbp_glrt_write(rt2x00dev, 173, 0x0D);
	rt2800_bbp_glrt_write(rt2x00dev, 174, 0x28);
	rt2800_bbp_glrt_write(rt2x00dev, 175, 0x21);
	rt2800_bbp_glrt_write(rt2x00dev, 176, 0x1C);
	rt2800_bbp_glrt_write(rt2x00dev, 177, 0x16);
	rt2800_bbp_glrt_write(rt2x00dev, 178, 0x50);
	rt2800_bbp_glrt_write(rt2x00dev, 179, 0x4A);
	rt2800_bbp_glrt_write(rt2x00dev, 180, 0x43);
	rt2800_bbp_glrt_write(rt2x00dev, 181, 0x50);
	rt2800_bbp_glrt_write(rt2x00dev, 182, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 183, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 184, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 185, 0x10);
	rt2800_bbp_glrt_write(rt2x00dev, 200, 0x7D);
	rt2800_bbp_glrt_write(rt2x00dev, 201, 0x14);
	rt2800_bbp_glrt_write(rt2x00dev, 202, 0x32);
	rt2800_bbp_glrt_write(rt2x00dev, 203, 0x2C);
	rt2800_bbp_glrt_write(rt2x00dev, 204, 0x36);
	rt2800_bbp_glrt_write(rt2x00dev, 205, 0x4C);
	rt2800_bbp_glrt_write(rt2x00dev, 206, 0x43);
	rt2800_bbp_glrt_write(rt2x00dev, 207, 0x2C);
	rt2800_bbp_glrt_write(rt2x00dev, 208, 0x2E);
	rt2800_bbp_glrt_write(rt2x00dev, 209, 0x36);
	rt2800_bbp_glrt_write(rt2x00dev, 210, 0x30);
	rt2800_bbp_glrt_write(rt2x00dev, 211, 0x6E);

	/* BBP for G band DCOC function */
	rt2800_bbp_dcoc_write(rt2x00dev, 140, 0x0C);
	rt2800_bbp_dcoc_write(rt2x00dev, 141, 0x00);
	rt2800_bbp_dcoc_write(rt2x00dev, 142, 0x10);
	rt2800_bbp_dcoc_write(rt2x00dev, 143, 0x10);
	rt2800_bbp_dcoc_write(rt2x00dev, 144, 0x10);
	rt2800_bbp_dcoc_write(rt2x00dev, 145, 0x10);
	rt2800_bbp_dcoc_write(rt2x00dev, 146, 0x08);
	rt2800_bbp_dcoc_write(rt2x00dev, 147, 0x40);
	rt2800_bbp_dcoc_write(rt2x00dev, 148, 0x04);
	rt2800_bbp_dcoc_write(rt2x00dev, 149, 0x04);
	rt2800_bbp_dcoc_write(rt2x00dev, 150, 0x08);
	rt2800_bbp_dcoc_write(rt2x00dev, 151, 0x08);
	rt2800_bbp_dcoc_write(rt2x00dev, 152, 0x03);
	rt2800_bbp_dcoc_write(rt2x00dev, 153, 0x03);
	rt2800_bbp_dcoc_write(rt2x00dev, 154, 0x03);
	rt2800_bbp_dcoc_write(rt2x00dev, 155, 0x02);
	rt2800_bbp_dcoc_write(rt2x00dev, 156, 0x40);
	rt2800_bbp_dcoc_write(rt2x00dev, 157, 0x40);
	rt2800_bbp_dcoc_write(rt2x00dev, 158, 0x64);
	rt2800_bbp_dcoc_write(rt2x00dev, 159, 0x64);

	rt2800_bbp4_mac_if_ctrl(rt2x00dev);
}