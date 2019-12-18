#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* UTF8_EncoderAttr ;
struct TYPE_7__ {scalar_t__* cid_map; } ;
struct TYPE_6__ {scalar_t__ attr; } ;
struct TYPE_5__ {int end_byte; int* utf8_bytes; } ;
typedef  unsigned int HPDF_UNICODE ;
typedef  int /*<<< orphan*/  HPDF_UINT16 ;
typedef  TYPE_2__* HPDF_Encoder ;
typedef  TYPE_3__* HPDF_CMapEncoderAttr ;

/* Variables and functions */

__attribute__((used)) static HPDF_UNICODE
UTF8_Encoder_ToUnicode_Func  (HPDF_Encoder   encoder,
                              HPDF_UINT16    code)
{
    // Supposed to convert CODE to unicode.
    // This function is allways called after ByteType_Func.
    // ByteType_Func recognizes the utf-8 bytes belonging to one character.

    HPDF_CMapEncoderAttr encoder_attr;
    UTF8_EncoderAttr     utf8_attr;
    unsigned int         val;

    encoder_attr = (HPDF_CMapEncoderAttr) encoder->attr;
    utf8_attr = (UTF8_EncoderAttr) ((void *)encoder_attr->cid_map[0]);

    switch (utf8_attr->end_byte) {
    case 3:
	val = (unsigned int) ((utf8_attr->utf8_bytes[0] & 0x7) << 18) +
	    (unsigned int) ((utf8_attr->utf8_bytes[1]) << 12)       +
	    (unsigned int) ((utf8_attr->utf8_bytes[2] & 0x3f) << 6) +
	    (unsigned int) ((utf8_attr->utf8_bytes[3] & 0x3f));
	break;
    case 2:
	val = (unsigned int) ((utf8_attr->utf8_bytes[0] & 0xf) << 12) +
	    (unsigned int) ((utf8_attr->utf8_bytes[1] & 0x3f) << 6) +
	    (unsigned int) ((utf8_attr->utf8_bytes[2] & 0x3f));
	break;
    case 1:
	val = (unsigned int) ((utf8_attr->utf8_bytes[0] & 0x1f) << 6) +
	    (unsigned int) ((utf8_attr->utf8_bytes[1] & 0x3f));
	break;
    case 0:
	val = (unsigned int)  utf8_attr->utf8_bytes[0];
	break;
    default:
	val = 32; // Unknown character
    }

    if (val > 65535) //Convert everything outside UCS-2 to space
        val = 32;

    return val;
}