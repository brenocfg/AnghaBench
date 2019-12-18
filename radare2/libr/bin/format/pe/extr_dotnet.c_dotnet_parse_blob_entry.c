#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int size; int length; } ;
struct TYPE_6__ {int const* data; int data_size; } ;
typedef  TYPE_1__ PE ;
typedef  int DWORD ;
typedef  TYPE_2__ BLOB_PARSE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  fits_in_pe (TYPE_1__*,int const*,int) ; 

BLOB_PARSE_RESULT dotnet_parse_blob_entry( PE* pe, const uint8_t* offset) {
	BLOB_PARSE_RESULT result;

	// Blob size is encoded in the first 1, 2 or 4 bytes of the blob.
	//
	// If the high bit is not set the length is encoded in one byte.
	//
	// If the high 2 bits are 10 (base 2) then the length is encoded in
	// the rest of the bits and the next byte.
	//
	// If the high 3 bits are 110 (base 2) then the length is encoded
	// in the rest of the bits and the next 3 bytes.
	//
	// See ECMA-335 II.24.2.4 for details.

	// Make sure we have at least one byte.

	if (!fits_in_pe(pe, offset, 1)) {
		result.size = 0;
		return result;
	}

	if ((*offset & 0x80) == 0x00) {
		result.length = (DWORD) *offset;
		result.size = 1;
	} else if ((*offset & 0xC0) == 0x80) {
		// Make sure we have one more byte.
		if (!fits_in_pe(pe, offset, 2)) {
			result.size = 0;
			return result;
		}

		// Shift remaining 6 bits left by 8 and OR in the remaining byte.
		result.length = ((*offset & 0x3F) << 8) | *(offset + 1);
		result.size = 2;
	} else if (offset + 4 < pe->data + pe->data_size && (*offset & 0xE0) == 0xC0) {
		// Make sure we have 3 more bytes.
		if (!fits_in_pe(pe, offset, 4)) {
			result.size = 0;
			return result;
		}

		result.length = ((*offset & 0x1F) << 24) |
			(*(offset + 1) << 16) |
			(*(offset + 2) << 8) |
			*(offset + 3);
		result.size = 4;
	} else {
		// Return a 0 size as an error.
		result.size = 0;
	}
	return result;
}