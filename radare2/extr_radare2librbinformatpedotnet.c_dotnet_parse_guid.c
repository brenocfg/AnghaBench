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
typedef  int ut64 ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int* data; int /*<<< orphan*/  object; } ;
struct TYPE_6__ {int Offset; int Size; } ;
typedef  TYPE_1__* PSTREAM_HEADER ;
typedef  TYPE_2__ PE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ fits_in_pe (TYPE_2__*,int const*,int) ; 
 int /*<<< orphan*/  set_integer (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_string (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int const,int const,int const,int const,int const,int const,int const,int const) ; 

void dotnet_parse_guid( PE* pe, ut64 metadata_root, PSTREAM_HEADER guid_header) {
	// GUIDs are 16 bytes each, converted to hex format plus separators and NULL.
	char guid[37];
	int i = 0;

	const uint8_t* guid_offset = pe->data + metadata_root + guid_header->Offset;
	DWORD guid_size = guid_header->Size;

	// Parse GUIDs if we have them.
	// GUIDs are 16 bytes each.
	while (guid_size >= 16 && fits_in_pe(pe, guid_offset, 16)) {
		sprintf(guid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
				*(uint32_t*) guid_offset,
				*(uint16_t*) (guid_offset + 4),
				*(uint16_t*) (guid_offset + 6),
				*(guid_offset + 8),
				*(guid_offset + 9),
				*(guid_offset + 10),
				*(guid_offset + 11),
				*(guid_offset + 12),
				*(guid_offset + 13),
				*(guid_offset + 14),
				*(guid_offset + 15));
		guid[(16 * 2) + 4] = '\0';
		set_string (guid, pe->object, "guids[%i]", i);
		i++;
		guid_size -= 16;
	}
	set_integer(i, pe->object, "number_of_guids");
}