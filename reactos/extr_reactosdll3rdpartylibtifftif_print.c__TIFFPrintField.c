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
typedef  int uint8 ;
typedef  scalar_t__ uint64 ;
typedef  size_t uint32 ;
typedef  int uint16 ;
typedef  int int8 ;
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;
typedef  int int16 ;
struct TYPE_3__ {char* field_name; scalar_t__ field_type; } ;
typedef  TYPE_1__ TIFFField ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ TIFF_ASCII ; 
 scalar_t__ TIFF_BYTE ; 
 scalar_t__ TIFF_DOUBLE ; 
 scalar_t__ TIFF_FLOAT ; 
 scalar_t__ TIFF_IFD ; 
 scalar_t__ TIFF_IFD8 ; 
 scalar_t__ TIFF_LONG ; 
 scalar_t__ TIFF_LONG8 ; 
 scalar_t__ TIFF_RATIONAL ; 
 scalar_t__ TIFF_SBYTE ; 
 scalar_t__ TIFF_SHORT ; 
 scalar_t__ TIFF_SLONG ; 
 scalar_t__ TIFF_SLONG8 ; 
 scalar_t__ TIFF_SRATIONAL ; 
 scalar_t__ TIFF_SSHORT ; 
 scalar_t__ TIFF_UNDEFINED ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
_TIFFPrintField(FILE* fd, const TIFFField *fip,
		uint32 value_count, void *raw_data)
{
	uint32 j;
		
	fprintf(fd, "  %s: ", fip->field_name);

	for(j = 0; j < value_count; j++) {
		if(fip->field_type == TIFF_BYTE)
			fprintf(fd, "%u", ((uint8 *) raw_data)[j]);
		else if(fip->field_type == TIFF_UNDEFINED)
			fprintf(fd, "0x%x",
			    (unsigned int) ((unsigned char *) raw_data)[j]);
		else if(fip->field_type == TIFF_SBYTE)
			fprintf(fd, "%d", ((int8 *) raw_data)[j]);
		else if(fip->field_type == TIFF_SHORT)
			fprintf(fd, "%u", ((uint16 *) raw_data)[j]);
		else if(fip->field_type == TIFF_SSHORT)
			fprintf(fd, "%d", ((int16 *) raw_data)[j]);
		else if(fip->field_type == TIFF_LONG)
			fprintf(fd, "%lu",
			    (unsigned long)((uint32 *) raw_data)[j]);
		else if(fip->field_type == TIFF_SLONG)
			fprintf(fd, "%ld", (long)((int32 *) raw_data)[j]);
		else if(fip->field_type == TIFF_IFD)
			fprintf(fd, "0x%lx",
				(unsigned long)((uint32 *) raw_data)[j]);
		else if(fip->field_type == TIFF_RATIONAL
			|| fip->field_type == TIFF_SRATIONAL
			|| fip->field_type == TIFF_FLOAT)
			fprintf(fd, "%f", ((float *) raw_data)[j]);
		else if(fip->field_type == TIFF_LONG8)
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			fprintf(fd, "%I64u",
			    (unsigned __int64)((uint64 *) raw_data)[j]);
#else
			fprintf(fd, "%llu",
			    (unsigned long long)((uint64 *) raw_data)[j]);
#endif
		else if(fip->field_type == TIFF_SLONG8)
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			fprintf(fd, "%I64d", (__int64)((int64 *) raw_data)[j]);
#else
			fprintf(fd, "%lld", (long long)((int64 *) raw_data)[j]);
#endif
		else if(fip->field_type == TIFF_IFD8)
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
			fprintf(fd, "0x%I64x",
				(unsigned __int64)((uint64 *) raw_data)[j]);
#else
			fprintf(fd, "0x%llx",
				(unsigned long long)((uint64 *) raw_data)[j]);
#endif
		else if(fip->field_type == TIFF_FLOAT)
			fprintf(fd, "%f", ((float *)raw_data)[j]);
		else if(fip->field_type == TIFF_DOUBLE)
			fprintf(fd, "%f", ((double *) raw_data)[j]);
		else if(fip->field_type == TIFF_ASCII) {
			fprintf(fd, "%s", (char *) raw_data);
			break;
		}
		else {
			fprintf(fd, "<unsupported data type in TIFFPrint>");
			break;
		}

		if(j < value_count - 1)
			fprintf(fd, ",");
	}

	fprintf(fd, "\n");
}