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
typedef  int /*<<< orphan*/  xbuf ;
typedef  int /*<<< orphan*/  bbuf ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
#define  GUC_UNIT_BLOCKS 135 
#define  GUC_UNIT_BYTE 134 
#define  GUC_UNIT_KB 133 
#define  GUC_UNIT_MB 132 
 int GUC_UNIT_MEMORY ; 
#define  GUC_UNIT_MIN 131 
#define  GUC_UNIT_MS 130 
#define  GUC_UNIT_S 129 
 int GUC_UNIT_TIME ; 
#define  GUC_UNIT_XBLOCKS 128 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
get_config_unit_name(int flags)
{
	switch (flags & (GUC_UNIT_MEMORY | GUC_UNIT_TIME))
	{
		case 0:
			return NULL;		/* GUC has no units */
		case GUC_UNIT_BYTE:
			return "B";
		case GUC_UNIT_KB:
			return "kB";
		case GUC_UNIT_MB:
			return "MB";
		case GUC_UNIT_BLOCKS:
			{
				static char bbuf[8];

				/* initialize if first time through */
				if (bbuf[0] == '\0')
					snprintf(bbuf, sizeof(bbuf), "%dkB", BLCKSZ / 1024);
				return bbuf;
			}
		case GUC_UNIT_XBLOCKS:
			{
				static char xbuf[8];

				/* initialize if first time through */
				if (xbuf[0] == '\0')
					snprintf(xbuf, sizeof(xbuf), "%dkB", XLOG_BLCKSZ / 1024);
				return xbuf;
			}
		case GUC_UNIT_MS:
			return "ms";
		case GUC_UNIT_S:
			return "s";
		case GUC_UNIT_MIN:
			return "min";
		default:
			elog(ERROR, "unrecognized GUC units value: %d",
				 flags & (GUC_UNIT_MEMORY | GUC_UNIT_TIME));
			return NULL;
	}
}