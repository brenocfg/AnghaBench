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
#define  JFFS2_COMPR_MODE_FORCELZO 130 
#define  JFFS2_COMPR_MODE_FORCEZLIB 129 
#define  JFFS2_COMPR_MODE_NONE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static const char *jffs2_compr_name(unsigned int compr)
{
	switch (compr) {
	case JFFS2_COMPR_MODE_NONE:
		return "none";
#ifdef CONFIG_JFFS2_LZO
	case JFFS2_COMPR_MODE_FORCELZO:
		return "lzo";
#endif
#ifdef CONFIG_JFFS2_ZLIB
	case JFFS2_COMPR_MODE_FORCEZLIB:
		return "zlib";
#endif
	default:
		/* should never happen; programmer error */
		WARN_ON(1);
		return "";
	}
}