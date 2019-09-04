#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int uint8_t ;
struct TYPE_11__ {scalar_t__ size; int length; } ;
struct TYPE_10__ {int* data; int /*<<< orphan*/  object; } ;
struct TYPE_9__ {int Offset; int Size; } ;
typedef  TYPE_1__* PSTREAM_HEADER ;
typedef  TYPE_2__ PE ;
typedef  TYPE_3__ BLOB_PARSE_RESULT ;

/* Variables and functions */
 TYPE_3__ dotnet_parse_blob_entry (TYPE_2__*,int const*) ; 
 int /*<<< orphan*/  fits_in_pe (TYPE_2__*,int const*,int) ; 
 int /*<<< orphan*/  set_integer (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_sized_string (char*,scalar_t__,int /*<<< orphan*/ ,char*,int) ; 

void dotnet_parse_us( PE* pe, ut64 metadata_root, PSTREAM_HEADER us_header) {
	BLOB_PARSE_RESULT blob_result;
	int i = 0;

	const uint8_t* offset = pe->data + metadata_root + us_header->Offset;
	const uint8_t* end_of_header = offset + us_header->Size;

	// Make sure end of header is not past end of PE, and the first entry MUST be
	// a single NULL byte.
	if (!fits_in_pe(pe, offset, us_header->Size) || *offset != 0x00) {
		return;
	}

	offset++;

	while (offset < end_of_header) {
		blob_result = dotnet_parse_blob_entry(pe, offset);

		if (blob_result.size == 0 || !fits_in_pe(pe, offset, blob_result.length)) {
			set_integer(i, pe->object, "number_of_user_strings");
			return;
		}

		offset += blob_result.size;
		// Avoid empty strings, which usually happen as padding at the end of the
		// stream.

		if (blob_result.length > 0) {
			set_sized_string(
					(char*) offset,
					blob_result.length,
					pe->object,
					"user_strings[%i]",
					i);

			offset += blob_result.length;
			i++;
		}
	}

	set_integer(i, pe->object, "number_of_user_strings");
}