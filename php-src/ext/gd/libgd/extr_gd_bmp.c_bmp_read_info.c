#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_6__ {int len; } ;
typedef  TYPE_1__ bmp_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMP_DEBUG (int /*<<< orphan*/ ) ; 
#define  BMP_OS2_V1 132 
#define  BMP_OS2_V2 131 
#define  BMP_WINDOWS_V3 130 
#define  BMP_WINDOWS_V4 129 
#define  BMP_WINDOWS_V5 128 
 int /*<<< orphan*/  bmp_read_os2_v1_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  bmp_read_os2_v2_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  bmp_read_windows_v3_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gdGetIntLSB (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int bmp_read_info(gdIOCtx *infile, bmp_info_t *info)
{
	/* read BMP length so we can work out the version */
	if (!gdGetIntLSB(&info->len, infile)) {
		return 1;
	}

	switch (info->len) {
		/* For now treat Windows v4 + v5 as v3 */
	case BMP_WINDOWS_V3:
	case BMP_WINDOWS_V4:
	case BMP_WINDOWS_V5:
		BMP_DEBUG(printf("Reading Windows Header\n"));
		if (bmp_read_windows_v3_info(infile, info)) {
			return 1;
		}
		break;
	case BMP_OS2_V1:
		if (bmp_read_os2_v1_info(infile, info)) {
			return 1;
		}
		break;
	case BMP_OS2_V2:
		if (bmp_read_os2_v2_info(infile, info)) {
			return 1;
		}
		break;
	default:
		BMP_DEBUG(printf("Unhandled bitmap\n"));
		return 1;
	}
	return 0;
}