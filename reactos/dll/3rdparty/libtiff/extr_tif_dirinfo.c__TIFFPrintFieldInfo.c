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
typedef  size_t uint32 ;
struct TYPE_5__ {char* tif_name; size_t tif_nfields; TYPE_1__** tif_fields; } ;
struct TYPE_4__ {int /*<<< orphan*/  field_name; scalar_t__ field_passcount; scalar_t__ field_oktochange; int /*<<< orphan*/  field_bit; int /*<<< orphan*/  field_type; int /*<<< orphan*/  field_writecount; int /*<<< orphan*/  field_readcount; scalar_t__ field_tag; } ;
typedef  TYPE_1__ TIFFField ;
typedef  TYPE_2__ TIFF ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
_TIFFPrintFieldInfo(TIFF* tif, FILE* fd)
{
	uint32 i;

	fprintf(fd, "%s: \n", tif->tif_name);
	for (i = 0; i < tif->tif_nfields; i++) {
		const TIFFField* fip = tif->tif_fields[i];
		fprintf(fd, "field[%2d] %5lu, %2d, %2d, %d, %2d, %5s, %5s, %s\n"
			, (int)i
			, (unsigned long) fip->field_tag
			, fip->field_readcount, fip->field_writecount
			, fip->field_type
			, fip->field_bit
			, fip->field_oktochange ? "TRUE" : "FALSE"
			, fip->field_passcount ? "TRUE" : "FALSE"
			, fip->field_name
		);
	}
}