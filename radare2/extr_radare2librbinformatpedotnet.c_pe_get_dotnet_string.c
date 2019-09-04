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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int data_size; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ PE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ memmem (void*,size_t,char*,int) ; 

char* pe_get_dotnet_string( PE* pe, const uint8_t* string_offset, DWORD string_index) {
	// Start of string must be within boundary
	if (!(string_offset + string_index >= pe->data &&
			string_offset + string_index < pe->data + pe->data_size)) {
		return NULL;
	}
	// Calculate how much until end of boundary, don't scan past that.
	size_t remaining = (pe->data + pe->data_size) - (string_offset + string_index);

	// Search for a NULL terminator from start of string, up to remaining.
	char *start = (char*) (string_offset + string_index);
	char *eos = (char*) memmem((void*) start, remaining, "\0", 1);

	return eos? start: NULL;
}