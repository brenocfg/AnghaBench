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
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_2__ {unsigned char disposal; unsigned char inputFlag; int /*<<< orphan*/  delayTime; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GetDataBlock (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 TYPE_1__ Gif89 ; 
 int /*<<< orphan*/  LM_to_uint (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
DoExtension(gdIOCtx *fd, int label, int *Transparent, int *ZeroDataBlockP)
{
	unsigned char buf[256];

	switch (label) {
		case 0xf9:              /* Graphic Control Extension */
			memset(buf, 0, 4); /* initialize a few bytes in the case the next function fails */
               (void) GetDataBlock(fd, (unsigned char*) buf, ZeroDataBlockP);
#if 0
			Gif89.disposal    = (buf[0] >> 2) & 0x7;
			Gif89.inputFlag   = (buf[0] >> 1) & 0x1;
			Gif89.delayTime   = LM_to_uint(buf[1],buf[2]);
#endif
			if ((buf[0] & 0x1) != 0)
				*Transparent = buf[3];

			while (GetDataBlock(fd, (unsigned char*) buf, ZeroDataBlockP) > 0);
			return FALSE;
		default:
			break;
	}
       while (GetDataBlock(fd, (unsigned char*) buf, ZeroDataBlockP) > 0)
		;

	return FALSE;
}