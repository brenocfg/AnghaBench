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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  MESON_SOCINFO_MAJOR_VER_MESON6 130 
#define  MESON_SOCINFO_MAJOR_VER_MESON8 129 
#define  MESON_SOCINFO_MAJOR_VER_MESON8B 128 
 char const* kasprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static const char *meson_mx_socinfo_revision(unsigned int major_ver,
					     unsigned int misc_ver,
					     unsigned int metal_rev)
{
	unsigned int minor_ver;

	switch (major_ver) {
	case MESON_SOCINFO_MAJOR_VER_MESON6:
		minor_ver = 0xa;
		break;

	case MESON_SOCINFO_MAJOR_VER_MESON8:
		if (metal_rev == 0x11111112)
			major_ver = 0x1d;

		if (metal_rev == 0x11111111 || metal_rev == 0x11111112)
			minor_ver = 0xa;
		else if (metal_rev == 0x11111113)
			minor_ver = 0xb;
		else if (metal_rev == 0x11111133)
			minor_ver = 0xc;
		else
			minor_ver = 0xd;

		break;

	case MESON_SOCINFO_MAJOR_VER_MESON8B:
		if (metal_rev == 0x11111111)
			minor_ver = 0xa;
		else
			minor_ver = 0xb;

		break;

	default:
		minor_ver = 0x0;
		break;
	}

	return kasprintf(GFP_KERNEL, "Rev%X (%x - 0:%X)", minor_ver, major_ver,
			 misc_ver);
}