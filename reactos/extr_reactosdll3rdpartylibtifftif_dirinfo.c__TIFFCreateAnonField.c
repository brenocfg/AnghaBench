#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_5__ {int field_type; char* field_name; int /*<<< orphan*/ * field_subfields; void* field_passcount; void* field_oktochange; int /*<<< orphan*/  field_bit; void* get_field_type; void* set_field_type; scalar_t__ reserved; void* field_writecount; void* field_readcount; scalar_t__ field_tag; } ;
typedef  TYPE_1__ TIFFField ;
typedef  int TIFFDataType ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_CUSTOM ; 
#define  TIFF_ASCII 143 
#define  TIFF_BYTE 142 
#define  TIFF_DOUBLE 141 
#define  TIFF_FLOAT 140 
#define  TIFF_IFD 139 
#define  TIFF_IFD8 138 
#define  TIFF_LONG 137 
#define  TIFF_LONG8 136 
#define  TIFF_RATIONAL 135 
#define  TIFF_SBYTE 134 
 void* TIFF_SETGET_C32_ASCII ; 
 void* TIFF_SETGET_C32_DOUBLE ; 
 void* TIFF_SETGET_C32_FLOAT ; 
 void* TIFF_SETGET_C32_IFD8 ; 
 void* TIFF_SETGET_C32_SINT16 ; 
 void* TIFF_SETGET_C32_SINT32 ; 
 void* TIFF_SETGET_C32_SINT64 ; 
 void* TIFF_SETGET_C32_SINT8 ; 
 void* TIFF_SETGET_C32_UINT16 ; 
 void* TIFF_SETGET_C32_UINT32 ; 
 void* TIFF_SETGET_C32_UINT64 ; 
 void* TIFF_SETGET_C32_UINT8 ; 
 void* TIFF_SETGET_UNDEFINED ; 
#define  TIFF_SHORT 133 
#define  TIFF_SLONG 132 
#define  TIFF_SLONG8 131 
#define  TIFF_SRATIONAL 130 
#define  TIFF_SSHORT 129 
#define  TIFF_UNDEFINED 128 
 void* TIFF_VARIABLE2 ; 
 void* TRUE ; 
 int /*<<< orphan*/  _TIFFfree (TYPE_1__*) ; 
 scalar_t__ _TIFFmalloc (int) ; 
 int /*<<< orphan*/  _TIFFmemset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

TIFFField*
_TIFFCreateAnonField(TIFF *tif, uint32 tag, TIFFDataType field_type)
{
	TIFFField *fld;
	(void) tif;

	fld = (TIFFField *) _TIFFmalloc(sizeof (TIFFField));
	if (fld == NULL)
	    return NULL;
	_TIFFmemset(fld, 0, sizeof(TIFFField));

	fld->field_tag = tag;
	fld->field_readcount = TIFF_VARIABLE2;
	fld->field_writecount = TIFF_VARIABLE2;
	fld->field_type = field_type;
	fld->reserved = 0;
	switch (field_type)
	{
		case TIFF_BYTE:
		case TIFF_UNDEFINED:
			fld->set_field_type = TIFF_SETGET_C32_UINT8;
			fld->get_field_type = TIFF_SETGET_C32_UINT8;
			break;
		case TIFF_ASCII:
			fld->set_field_type = TIFF_SETGET_C32_ASCII;
			fld->get_field_type = TIFF_SETGET_C32_ASCII;
			break;
		case TIFF_SHORT:
			fld->set_field_type = TIFF_SETGET_C32_UINT16;
			fld->get_field_type = TIFF_SETGET_C32_UINT16;
			break;
		case TIFF_LONG:
			fld->set_field_type = TIFF_SETGET_C32_UINT32;
			fld->get_field_type = TIFF_SETGET_C32_UINT32;
			break;
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
		case TIFF_FLOAT:
			fld->set_field_type = TIFF_SETGET_C32_FLOAT;
			fld->get_field_type = TIFF_SETGET_C32_FLOAT;
			break;
		case TIFF_SBYTE:
			fld->set_field_type = TIFF_SETGET_C32_SINT8;
			fld->get_field_type = TIFF_SETGET_C32_SINT8;
			break;
		case TIFF_SSHORT:
			fld->set_field_type = TIFF_SETGET_C32_SINT16;
			fld->get_field_type = TIFF_SETGET_C32_SINT16;
			break;
		case TIFF_SLONG:
			fld->set_field_type = TIFF_SETGET_C32_SINT32;
			fld->get_field_type = TIFF_SETGET_C32_SINT32;
			break;
		case TIFF_DOUBLE:
			fld->set_field_type = TIFF_SETGET_C32_DOUBLE;
			fld->get_field_type = TIFF_SETGET_C32_DOUBLE;
			break;
		case TIFF_IFD:
		case TIFF_IFD8:
			fld->set_field_type = TIFF_SETGET_C32_IFD8;
			fld->get_field_type = TIFF_SETGET_C32_IFD8;
			break;
		case TIFF_LONG8:
			fld->set_field_type = TIFF_SETGET_C32_UINT64;
			fld->get_field_type = TIFF_SETGET_C32_UINT64;
			break;
		case TIFF_SLONG8:
			fld->set_field_type = TIFF_SETGET_C32_SINT64;
			fld->get_field_type = TIFF_SETGET_C32_SINT64;
			break;
		default:
			fld->set_field_type = TIFF_SETGET_UNDEFINED;
			fld->get_field_type = TIFF_SETGET_UNDEFINED;
			break;
	}
	fld->field_bit = FIELD_CUSTOM;
	fld->field_oktochange = TRUE;
	fld->field_passcount = TRUE;
	fld->field_name = (char *) _TIFFmalloc(32);
	if (fld->field_name == NULL) {
	    _TIFFfree(fld);
	    return NULL;
	}
	fld->field_subfields = NULL;

	/* 
	 * note that this name is a special sign to TIFFClose() and
	 * _TIFFSetupFields() to free the field
	 */
	(void) snprintf(fld->field_name, 32, "Tag %d", (int) tag);

	return fld;    
}