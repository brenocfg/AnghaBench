#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {char* cur; } ;
typedef  TYPE_1__ SB ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sb_need (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  to_surrogate_pair (int,int*,int*) ; 
 int /*<<< orphan*/  utf8_read_char (char const*,int*) ; 
 int utf8_validate (char const*) ; 
 int utf8_validate_cz (char const*) ; 
 int /*<<< orphan*/  write_hex16 (char*,int) ; 

void emit_string(SB *out, const char *str)
{
	bool escape_unicode = false;
	const char *s = str;
	char *b;
	
	assert(utf8_validate(str));
	
	/*
	 * 14 bytes is enough space to write up to two
	 * \uXXXX escapes and two quotation marks.
	 */
	sb_need(out, 14);
	b = out->cur;
	
	*b++ = '"';
	while (*s != 0) {
		unsigned char c = *s++;
		
		/* Encode the next character, and write it to b. */
		switch (c) {
			case '"':
				*b++ = '\\';
				*b++ = '"';
				break;
			case '\\':
				*b++ = '\\';
				*b++ = '\\';
				break;
			case '\b':
				*b++ = '\\';
				*b++ = 'b';
				break;
			case '\f':
				*b++ = '\\';
				*b++ = 'f';
				break;
			case '\n':
				*b++ = '\\';
				*b++ = 'n';
				break;
			case '\r':
				*b++ = '\\';
				*b++ = 'r';
				break;
			case '\t':
				*b++ = '\\';
				*b++ = 't';
				break;
			default: {
				int len;
				
				s--;
				len = utf8_validate_cz(s);
				
				if (len == 0) {
					/*
					 * Handle invalid UTF-8 character gracefully in production
					 * by writing a replacement character (U+FFFD)
					 * and skipping a single byte.
					 *
					 * This should never happen when assertions are enabled
					 * due to the assertion at the beginning of this function.
					 */
					assert(false);
					if (escape_unicode) {
						strcpy(b, "\\uFFFD");
						b += 6;
					} else {
						*b++ = 0xEF;
						*b++ = 0xBF;
						*b++ = 0xBD;
					}
					s++;
				} else if (c < 0x1F || (c >= 0x80 && escape_unicode)) {
					/* Encode using \u.... */
					uint32_t unicode;
					
					s += utf8_read_char(s, &unicode);
					
					if (unicode <= 0xFFFF) {
						*b++ = '\\';
						*b++ = 'u';
						b += write_hex16(b, unicode);
					} else {
						/* Produce a surrogate pair. */
						uint16_t uc, lc;
						assert(unicode <= 0x10FFFF);
						to_surrogate_pair(unicode, &uc, &lc);
						*b++ = '\\';
						*b++ = 'u';
						b += write_hex16(b, uc);
						*b++ = '\\';
						*b++ = 'u';
						b += write_hex16(b, lc);
					}
				} else {
					/* Write the character directly. */
					while (len--)
						*b++ = *s++;
				}
				
				break;
			}
		}
	
		/*
		 * Update *out to know about the new bytes,
		 * and set up b to write another encoded character.
		 */
		out->cur = b;
		sb_need(out, 14);
		b = out->cur;
	}
	*b++ = '"';
	
	out->cur = b;
}