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
typedef  int ut32 ;

/* Variables and functions */
 scalar_t__ dso_json_char_needs_hexing (char const) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const) ; 

__attribute__((used)) static char *convert_string(const char *bytes, ut32 len) {
	ut32 idx = 0, pos = 0;
	ut32 str_sz = 32 * len + 1;
	char *cpy_buffer = len > 0 ? malloc (str_sz) : NULL;
	if (!cpy_buffer) {
		return cpy_buffer;
	}
	// 4x is the increase from byte to \xHH where HH represents hexed byte
	memset (cpy_buffer, 0, str_sz);
	while (idx < len && pos < len) {
		if (dso_json_char_needs_hexing (bytes[idx])) {
			if (pos + 2 < len) {
				free (cpy_buffer);
				return NULL;
			}
			sprintf (cpy_buffer + pos, "\\x%02x", bytes[idx]);
			pos += 4;
		} else {
			cpy_buffer[pos] = bytes[idx];
			pos++;
		}
		idx++;
	}
	return cpy_buffer;
}