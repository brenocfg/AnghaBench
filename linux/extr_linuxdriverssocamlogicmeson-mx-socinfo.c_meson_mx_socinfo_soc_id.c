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
 char const* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *meson_mx_socinfo_soc_id(unsigned int major_ver,
					   unsigned int metal_rev)
{
	const char *soc_id;

	switch (major_ver) {
	case MESON_SOCINFO_MAJOR_VER_MESON6:
		soc_id = "Meson6 (AML8726-MX)";
		break;

	case MESON_SOCINFO_MAJOR_VER_MESON8:
		if (metal_rev == 0x11111112)
			soc_id = "Meson8m2 (S812)";
		else
			soc_id = "Meson8 (S802)";

		break;

	case MESON_SOCINFO_MAJOR_VER_MESON8B:
		soc_id = "Meson8b (S805)";
		break;

	default:
		soc_id = "Unknown";
		break;
	}

	return kstrdup_const(soc_id, GFP_KERNEL);
}