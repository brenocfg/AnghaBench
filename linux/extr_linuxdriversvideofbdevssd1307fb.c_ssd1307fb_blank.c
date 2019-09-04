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
struct ssd1307fb_par {int /*<<< orphan*/  client; } ;
struct fb_info {struct ssd1307fb_par* par; } ;

/* Variables and functions */
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  SSD1307FB_DISPLAY_OFF ; 
 int /*<<< orphan*/  SSD1307FB_DISPLAY_ON ; 
 int ssd1307fb_write_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssd1307fb_blank(int blank_mode, struct fb_info *info)
{
	struct ssd1307fb_par *par = info->par;

	if (blank_mode != FB_BLANK_UNBLANK)
		return ssd1307fb_write_cmd(par->client, SSD1307FB_DISPLAY_OFF);
	else
		return ssd1307fb_write_cmd(par->client, SSD1307FB_DISPLAY_ON);
}