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
typedef  int ut8 ;
typedef  int ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  clean_line (char*,char const*) ; 
 int decode_parameter (char*,int*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int dcpu16_assemble (ut8* out, const char* unoline) {
	ut16 wordA = 0, wordB = 0;
	int basic_opcode = 0;
	int non_basic_opcode = 0;
	char line[256] = {0}, *param;
	int off = 0;
	// uberflow!
	clean_line (line, unoline);
	
	if (!(*line)) return 0;
	if (strlen (line)<4) return 0;
	param = line + 3; /* Cut off first 3 characters */
	
	/* Basic instructions */
	// cmon! use an array
	if (!strncmp ("SET", line, 3)) basic_opcode = 0x1;
	else if (!strncmp ("ADD", line, 3)) basic_opcode = 0x2;
	else if (!strncmp ("SUB", line, 3)) basic_opcode = 0x3;
	else if (!strncmp ("MUL", line, 3)) basic_opcode = 0x4;
	else if (!strncmp ("DIV", line, 3)) basic_opcode = 0x5;
	else if (!strncmp ("MOD", line, 3)) basic_opcode = 0x6;
	else if (!strncmp ("SHL", line, 3)) basic_opcode = 0x7;
	else if (!strncmp ("SHR", line, 3)) basic_opcode = 0x8;
	else if (!strncmp ("AND", line, 3)) basic_opcode = 0x9;
	else if (!strncmp ("BOR", line, 3)) basic_opcode = 0xA;
	else if (!strncmp ("XOR", line, 3)) basic_opcode = 0xB;
	else if (!strncmp ("IFE", line, 3)) basic_opcode = 0xC;
	else if (!strncmp ("IFN", line, 3)) basic_opcode = 0xD;
	else if (!strncmp ("IFG", line, 3)) basic_opcode = 0xE;
	else if (!strncmp ("IFB", line, 3)) basic_opcode = 0xF;
	
	/* Non basic instructions */
	if (basic_opcode == 0) {
		if (!strncmp ("JSR", line, 3)) {
			non_basic_opcode = 0x1;
		} else {
			fprintf (stderr, "Unknown instruction\n");
			return -1;
		}
	}
	
	/* Decode basic instructions */
	if (basic_opcode != 0) {
		ut8 paramA = 0, paramB = 0;
		
		/* Find comma */
		int cn = 0;
		while (cn < 256
                        && param[cn] != ','
			&& param[cn] != '\n'
			&& param[cn] != 0)
			cn++;
			
		if (param[cn] == ',') {
			ut16 first_word;
			int extraA = 0;
			int extraB = 0;
			char *pa, *pb;
			/* Split parameter string to A and B */
			param[cn] = 0;
			pa = param;
			pb = param + cn + 1;
			
			/* Increment address for the start word */
			//current_address++;
			
			/* Parameter A */
			paramA = decode_parameter (pa, &extraA, &wordA);
			//if (extraA == 1) current_address++;
				
			/* Parameter B */
			paramB = decode_parameter(pb, &extraB, &wordB);
			//if (extraB == 1) current_address++;
				
			/* Put everything together */
			first_word = ((paramB & 0x3F) << 10) | ((paramA & 0x3F) << 4) | (basic_opcode & 0xF);

			/* write opcode */
#if NOTEND
			memcpy (out, &first_word, 2);
			if (extraA == 1) {
				memcpy (out+2, &wordA, 2);
				off = 4;
			} else off = 2;
			if (extraB == 1) {
				memcpy (out+off, &wordB, 2);
				off += 2;
			}
#else
			out[0] = (first_word>>8) & 0xff;
			out[1] = first_word & 0xff;
			if (extraA == 1) {
				out[2] = (wordA>>8) & 0xff;
				out[3] = wordA & 0xff;
				off = 4;
			} else off = 2;
			if (extraB == 1) {
				out[off] = (wordB>>8) & 0xff;
				out[off+1] = wordB & 0xff;
				off += 2;
			}
#endif
		} else {
			fprintf (stderr, "Missing comma\n");
			return -1;
		}
	}
	
	/* Non basic instructions */
	if (non_basic_opcode == 0x1) { /* JSR */
		int extraX = 0;
		ut16 first_word, wordX = 0;
		ut8 p = decode_parameter (param, &extraX, &wordX);

		first_word = ((p & 0x3F) << 10) \
			| ((non_basic_opcode & 0x3F) << 4) \
			| (basic_opcode & 0xF);
#if NOTEND
		memcpy (out, &first_word, 2);
		if (extraX == 1) {
			memcpy (out+2, &wordX, 2);
			off = 4;
		} else off = 2;
#else
		out[0] = (first_word>>8) & 0xff;
		out[1] = first_word & 0xff;
		if (extraX == 1) {
			out[2] = (wordX>>8) & 0xff;
			out[3] = wordX & 0xff;
			off = 4;
		} else off = 2;
#endif
	}
	return off;
}