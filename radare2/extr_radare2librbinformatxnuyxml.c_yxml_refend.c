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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTFROM5CHARS (char,unsigned char,char,char,unsigned char) ; 
 int /*<<< orphan*/  YXML_EREF ; 
 scalar_t__ yxml_isHex (unsigned int) ; 
 scalar_t__ yxml_isNum (unsigned int) ; 
 int /*<<< orphan*/  yxml_setutf8 (scalar_t__,unsigned int) ; 

__attribute__((used)) static yxml_ret_t yxml_refend(yxml_t *x, yxml_ret_t ret) {
	unsigned char *r = (unsigned char *)x->data;
	unsigned ch = 0;
	if(*r == '#') {
		if(r[1] == 'x')
			for(r += 2; yxml_isHex((unsigned)*r); r++)
				ch = (ch<<4) + (*r <= '9' ? *r-'0' : (*r|32)-'a' + 10);
		else
			for(r++; yxml_isNum((unsigned)*r); r++)
				ch = (ch*10) + (*r-'0');
		if(*r)
			ch = 0;
	} else {
		uint64_t i = INTFROM5CHARS(r[0], r[1], r[2], r[3], r[4]);
		ch =
			i == INTFROM5CHARS('l','t', 0,  0, 0) ? '<' :
			i == INTFROM5CHARS('g','t', 0,  0, 0) ? '>' :
			i == INTFROM5CHARS('a','m','p', 0, 0) ? '&' :
			i == INTFROM5CHARS('a','p','o','s',0) ? '\'':
			i == INTFROM5CHARS('q','u','o','t',0) ? '"' : 0;
	}

	/* Codepoints not allowed in the XML 1.1 definition of a Char */
	if(!ch || ch > 0x10FFFF || ch == 0xFFFE || ch == 0xFFFF || (ch-0xDFFF) < 0x7FF)
		return YXML_EREF;
	yxml_setutf8(x->data, ch);
	return ret;
}