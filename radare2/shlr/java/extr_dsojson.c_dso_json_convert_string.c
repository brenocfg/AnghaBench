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
 char* calloc (int,int) ; 
 scalar_t__ dso_json_char_needs_hexing (char const) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

char * dso_json_convert_string (const char * bytes, ut32 len) {
	ut32 idx = 0, pos = 1;
	ut32 str_sz = 4*len+1+2;
	char *cpy_buffer = len > 0 ? calloc (1, str_sz): NULL;
	if (!cpy_buffer) return cpy_buffer;
	// 4x is the increase from byte to \xHH where HH represents hexed byte
	cpy_buffer[0] = '"';
	while (idx < len) {
		if (bytes[idx] == '"') {
			sprintf (cpy_buffer+pos, "\\%c", bytes[idx]);
			pos += 2;
		} else if (dso_json_char_needs_hexing (bytes[idx])) {
			sprintf (cpy_buffer+pos, "\\x%02x", bytes[idx]);
			pos += 4;
		} else {
			cpy_buffer[pos] = bytes[idx];
			pos++;
		}
		idx ++;
	}
	strcat (cpy_buffer, "\"");
	return cpy_buffer;
}