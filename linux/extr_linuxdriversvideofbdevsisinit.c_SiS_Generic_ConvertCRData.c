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
struct fb_var_screeninfo {int xres; int left_margin; int right_margin; int hsync_len; int yres; int upper_margin; int lower_margin; int vsync_len; } ;
struct SiS_Private {int dummy; } ;

/* Variables and functions */

void
SiS_Generic_ConvertCRData(struct SiS_Private *SiS_Pr, unsigned char *crdata,
			int xres, int yres,
			struct fb_var_screeninfo *var, bool writeres
)
{
   unsigned short HRE, HBE, HRS, HBS, HDE, HT;
   unsigned short VRE, VBE, VRS, VBS, VDE, VT;
   unsigned char  sr_data, cr_data, cr_data2;
   int            A, B, C, D, E, F, temp;

   sr_data = crdata[14];

   /* Horizontal total */
   HT =  crdata[0] | ((unsigned short)(sr_data & 0x03) << 8);
   A = HT + 5;

   /* Horizontal display enable end */
   HDE = crdata[1] | ((unsigned short)(sr_data & 0x0C) << 6);
   E = HDE + 1;

   /* Horizontal retrace (=sync) start */
   HRS = crdata[4] | ((unsigned short)(sr_data & 0xC0) << 2);
   F = HRS - E - 3;

   /* Horizontal blank start */
   HBS = crdata[2] | ((unsigned short)(sr_data & 0x30) << 4);

   sr_data = crdata[15];
   cr_data = crdata[5];

   /* Horizontal blank end */
   HBE = (crdata[3] & 0x1f) |
         ((unsigned short)(cr_data & 0x80) >> 2) |
         ((unsigned short)(sr_data & 0x03) << 6);

   /* Horizontal retrace (=sync) end */
   HRE = (cr_data & 0x1f) | ((sr_data & 0x04) << 3);

   temp = HBE - ((E - 1) & 255);
   B = (temp > 0) ? temp : (temp + 256);

   temp = HRE - ((E + F + 3) & 63);
   C = (temp > 0) ? temp : (temp + 64);

   D = B - F - C;

   if(writeres) var->xres = xres = E * 8;
   var->left_margin = D * 8;
   var->right_margin = F * 8;
   var->hsync_len = C * 8;

   /* Vertical */
   sr_data = crdata[13];
   cr_data = crdata[7];

   /* Vertical total */
   VT  = crdata[6] |
	 ((unsigned short)(cr_data & 0x01) << 8) |
	 ((unsigned short)(cr_data & 0x20) << 4) |
	 ((unsigned short)(sr_data & 0x01) << 10);
   A = VT + 2;

   /* Vertical display enable end */
   VDE = crdata[10] |
	 ((unsigned short)(cr_data & 0x02) << 7) |
	 ((unsigned short)(cr_data & 0x40) << 3) |
	 ((unsigned short)(sr_data & 0x02) << 9);
   E = VDE + 1;

   /* Vertical retrace (=sync) start */
   VRS = crdata[8] |
	 ((unsigned short)(cr_data & 0x04) << 6) |
	 ((unsigned short)(cr_data & 0x80) << 2) |
	 ((unsigned short)(sr_data & 0x08) << 7);
   F = VRS + 1 - E;

   cr_data2 = (crdata[16] & 0x01) << 5;

   /* Vertical blank start */
   VBS = crdata[11] |
	 ((unsigned short)(cr_data  & 0x08) << 5) |
	 ((unsigned short)(cr_data2 & 0x20) << 4) |
	 ((unsigned short)(sr_data  & 0x04) << 8);

   /* Vertical blank end */
   VBE = crdata[12] | ((unsigned short)(sr_data & 0x10) << 4);
   temp = VBE - ((E - 1) & 511);
   B = (temp > 0) ? temp : (temp + 512);

   /* Vertical retrace (=sync) end */
   VRE = (crdata[9] & 0x0f) | ((sr_data & 0x20) >> 1);
   temp = VRE - ((E + F - 1) & 31);
   C = (temp > 0) ? temp : (temp + 32);

   D = B - F - C;

   if(writeres) var->yres = yres = E;
   var->upper_margin = D;
   var->lower_margin = F;
   var->vsync_len = C;

   if((xres == 320) && ((yres == 200) || (yres == 240))) {
	/* Terrible hack, but correct CRTC data for
	 * these modes only produces a black screen...
	 * (HRE is 0, leading into a too large C and
	 * a negative D. The CRT controller does not
	 * seem to like correcting HRE to 50)
	 */
      var->left_margin = (400 - 376);
      var->right_margin = (328 - 320);
      var->hsync_len = (376 - 328);

   }

}