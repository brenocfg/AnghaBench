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
struct nid_path {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NID_PATH_VOL_CTL ; 
 int add_vol_ctl (struct hda_codec*,char const*,int,int,struct nid_path*) ; 
 int get_default_ch_nums (struct hda_codec*,struct nid_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_stereo_vol(struct hda_codec *codec, const char *pfx, int cidx,
			  struct nid_path *path)
{
	int chs = get_default_ch_nums(codec, path, NID_PATH_VOL_CTL);
	return add_vol_ctl(codec, pfx, cidx, chs, path);
}