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
typedef  int TIFFDataType ;

/* Variables and functions */
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
#define  TIFF_SHORT 133 
#define  TIFF_SLONG 132 
#define  TIFF_SLONG8 131 
#define  TIFF_SRATIONAL 130 
#define  TIFF_SSHORT 129 
#define  TIFF_UNDEFINED 128 

int
TIFFDataWidth(TIFFDataType type)
{
	switch(type)
	{
		case 0:  /* nothing */
		case TIFF_BYTE:
		case TIFF_ASCII:
		case TIFF_SBYTE:
		case TIFF_UNDEFINED:
			return 1;
		case TIFF_SHORT:
		case TIFF_SSHORT:
			return 2;
		case TIFF_LONG:
		case TIFF_SLONG:
		case TIFF_FLOAT:
		case TIFF_IFD:
			return 4;
		case TIFF_RATIONAL:
		case TIFF_SRATIONAL:
		case TIFF_DOUBLE:
		case TIFF_LONG8:
		case TIFF_SLONG8:
		case TIFF_IFD8:
			return 8;
		default:
			return 0; /* will return 0 for unknown types */
	}
}