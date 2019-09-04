#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_3__ {int /*<<< orphan*/  field_type; int /*<<< orphan*/  field_name; } ;
typedef  TYPE_1__ TIFFField ;
typedef  int /*<<< orphan*/  TIFF ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  INKSET_CMYK 136 
#define  TIFFTAG_DOTRANGE 135 
#define  TIFFTAG_ICCPROFILE 134 
#define  TIFFTAG_INKSET 133 
#define  TIFFTAG_PHOTOSHOP 132 
#define  TIFFTAG_RICHTIFFIPTC 131 
#define  TIFFTAG_STONITS 130 
#define  TIFFTAG_WHITEPOINT 129 
#define  TIFFTAG_XMLPACKET 128 
 int /*<<< orphan*/  TIFF_DOUBLE ; 
 int /*<<< orphan*/  TIFF_RATIONAL ; 
 int /*<<< orphan*/  TIFF_SHORT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
_TIFFPrettyPrintField(TIFF* tif, const TIFFField *fip, FILE* fd, uint32 tag,
		      uint32 value_count, void *raw_data)
{
        (void) tif;

	/* do not try to pretty print auto-defined fields */
	if (strncmp(fip->field_name,"Tag ", 4) == 0) {
		return 0;
	}
        
	switch (tag)
	{
		case TIFFTAG_INKSET:
			if (value_count == 2 && fip->field_type == TIFF_SHORT) {
				fprintf(fd, "  Ink Set: ");
				switch (*((uint16*)raw_data)) {
				case INKSET_CMYK:
					fprintf(fd, "CMYK\n");
					break;
				default:
					fprintf(fd, "%u (0x%x)\n",
						*((uint16*)raw_data),
						*((uint16*)raw_data));
					break;
				}
				return 1;
			}
			return 0;

		case TIFFTAG_DOTRANGE:
			if (value_count == 2 && fip->field_type == TIFF_SHORT) {
				fprintf(fd, "  Dot Range: %u-%u\n",
					((uint16*)raw_data)[0], ((uint16*)raw_data)[1]);
				return 1;
			}
			return 0;

		case TIFFTAG_WHITEPOINT:
			if (value_count == 2 && fip->field_type == TIFF_RATIONAL) {
				fprintf(fd, "  White Point: %g-%g\n",
					((float *)raw_data)[0], ((float *)raw_data)[1]);
				return 1;
			} 
			return 0;

		case TIFFTAG_XMLPACKET:
		{
			uint32 i;

			fprintf(fd, "  XMLPacket (XMP Metadata):\n" );
			for(i = 0; i < value_count; i++)
				fputc(((char *)raw_data)[i], fd);
			fprintf( fd, "\n" );
			return 1;
		}
		case TIFFTAG_RICHTIFFIPTC:
			/*
			 * XXX: for some weird reason RichTIFFIPTC tag
			 * defined as array of LONG values.
			 */
			fprintf(fd,
			    "  RichTIFFIPTC Data: <present>, %lu bytes\n",
			    (unsigned long) value_count * 4);
			return 1;

		case TIFFTAG_PHOTOSHOP:
			fprintf(fd, "  Photoshop Data: <present>, %lu bytes\n",
			    (unsigned long) value_count);
			return 1;

		case TIFFTAG_ICCPROFILE:
			fprintf(fd, "  ICC Profile: <present>, %lu bytes\n",
			    (unsigned long) value_count);
			return 1;

		case TIFFTAG_STONITS:
			if (value_count == 1 && fip->field_type == TIFF_DOUBLE) { 
				fprintf(fd,
					"  Sample to Nits conversion factor: %.4e\n",
					*((double*)raw_data));
				return 1;
			}
			return 0;
	}

	return 0;
}