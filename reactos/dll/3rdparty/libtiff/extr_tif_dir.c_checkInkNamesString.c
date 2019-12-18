#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_4__ {scalar_t__ td_samplesperpixel; } ;
struct TYPE_5__ {int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
typedef  TYPE_1__ TIFFDirectory ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32
checkInkNamesString(TIFF* tif, uint32 slen, const char* s)
{
	TIFFDirectory* td = &tif->tif_dir;
	uint16 i = td->td_samplesperpixel;

	if (slen > 0) {
		const char* ep = s+slen;
		const char* cp = s;
		for (; i > 0; i--) {
			for (; cp < ep && *cp != '\0'; cp++) {}
			if (cp >= ep)
				goto bad;
			cp++;				/* skip \0 */
		}
		return ((uint32)(cp-s));
	}
bad:
	TIFFErrorExt(tif->tif_clientdata, "TIFFSetField",
	    "%s: Invalid InkNames value; expecting %d names, found %d",
	    tif->tif_name,
	    td->td_samplesperpixel,
	    td->td_samplesperpixel-i);
	return (0);
}