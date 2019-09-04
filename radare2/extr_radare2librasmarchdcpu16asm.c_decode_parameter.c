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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int get_register_id (char) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static ut8 decode_parameter(char* param, int* extra_word_needed, ut16* extra_word_value) {
	/* Check for square brackets */
	int square_brackets = 0;
	int first_sqbracket = 0, last_sqbracket = 0;
	if (param[0] == '[') {
		first_sqbracket = 1;
		param++;
	}
	if (param[strlen(param) - 1] == ']')  {
		last_sqbracket = 1;
		param[strlen(param) - 1] = 0;
	}
	
	/* Check for errors */
	if (first_sqbracket == 1) {
		square_brackets = 1;
		if (last_sqbracket != 1) {
			fprintf (stderr, "Missing last square bracket\n");
			return 0;
		}
	} else {
		if (last_sqbracket == 1) {
			fprintf (stderr, "Missing first square bracket\n");
			return 0;
		}
	}
	
	/* Check if this is a hex literal */
	if (param[0] == '0' && param[1] == 'X') {
		/* Decode hex */
		ut16 value = 0;
		param = param + 2; /* Remove 0x */
		int digit_count = strlen(param);
		int digit_num = 0;
		int reg = -1;
		for (digit_num = 0; digit_num < digit_count; digit_num++) {
			/* Get Digit value */
			int digit_val = -1;
			char current_digit = param[digit_num];
			if (current_digit >= '0' && current_digit <= '9')
				digit_val = current_digit - '0';
			if (current_digit >= 'A' && current_digit <= 'F')
				digit_val = current_digit - 'A' + 10;
				
			if (current_digit == '+' && square_brackets == 1) {
				reg = get_register_id(param[digit_num + 1]);
				digit_num++;
			} else {
				/* Check for errors */
				if (digit_val == -1) {
					fprintf (stderr, "invalid literal\n");
					return 0;
				}
				
				/* Merge into final number */
				value = (value << 4) + digit_val;
			}
		}
		
		if (value <= 0x1f && square_brackets == 0)
			return value + 0x20;
			
		*extra_word_needed = 1;
		*extra_word_value = value;
		
		if (square_brackets == 1) {
			if (reg != -1)
				return 0x10 + reg;
			return 0x1e;
		}
		return 0x1f;
	}
	
	/* Check if this is a decimal literal */
	if (param[0] >= '0' && param[0] <= '9') {
		/* Decode decimal */
		ut16 value = 0;
		int digit_count = strlen(param);
		int digit_num = 0;
		int reg = -1;
		for (digit_num = 0; digit_num < digit_count; digit_num++) {
			/* Get Digit value */
			int digit_val = -1;
			char current_digit = param[digit_num];
			if (current_digit >= '0' && current_digit <= '9')
				digit_val = current_digit - '0';
				
			if (current_digit == '+' && square_brackets == 1) {
				reg = get_register_id(param[digit_num + 1]);
				digit_num++;
			} else {
				/* Check for errors */
				if (digit_val == -1) {
					fprintf (stderr, "invalid literal\n");
					return 0;
				}
				
				/* Merge into final number */
				value = (value * 10) + digit_val;
			}
		}
		if (value <= 0x1f && square_brackets == 0)
			return value + 0x20;
			
		*extra_word_needed = 1;
		*extra_word_value = value;
		
		if (square_brackets == 1) {
			if (reg != -1)
				return 0x10 + reg;
			return 0x1e;
		}
		return 0x1f;
	}
	
	/* Check if this is a register */
	if (param[1] == 0) { /* This is a quick way to check that this is 1 character long */
		ut8 reg = get_register_id (param[0]);
		if (square_brackets == 1)
			reg += 0x08;
		return reg;
	}
	
	/* Check if this is a word */
	if (!strncmp ("POP", param, 3)) return 0x18;
	if (!strncmp ("PEEK", param, 4)) return 0x19;
	if (!strncmp ("PUSH", param, 4)) return 0x1a;
	if (!strncmp ("SP", param, 2)) return 0x1b;
	if (!strncmp ("PC", param, 2)) return 0x1c;
	if (!strncmp ("O", param, 1)) return 0x1d;
	
	/* Must be a label, store a labelref */
	*extra_word_needed = 1;
		/* Allocate blank extra word, this will be where the 
		   pointer to the label will be stored at link stage */
	*extra_word_value = 0; 
	return 0x1f;
}