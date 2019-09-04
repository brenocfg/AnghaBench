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

/* Variables and functions */
#define  ENT_HTML_DOC_HTML401 131 
#define  ENT_HTML_DOC_HTML5 130 
#define  ENT_HTML_DOC_XHTML 129 
#define  ENT_HTML_DOC_XML1 128 
 int unicode_cp_is_allowed (unsigned int,int) ; 

__attribute__((used)) static inline int numeric_entity_is_allowed(unsigned uni_cp, int document_type)
{
	/* less restrictive than unicode_cp_is_allowed */
	switch (document_type) {
	case ENT_HTML_DOC_HTML401:
		/* all non-SGML characters (those marked with UNUSED in DESCSET) should be
		 * representable with numeric entities */
		return uni_cp <= 0x10FFFF;
	case ENT_HTML_DOC_HTML5:
		/* 8.1.4. The numeric character reference forms described above are allowed to
		 * reference any Unicode code point other than U+0000, U+000D, permanently
		 * undefined Unicode characters (noncharacters), and control characters other
		 * than space characters (U+0009, U+000A, U+000C and U+000D) */
		/* seems to allow surrogate characters, then */
		return (uni_cp >= 0x20 && uni_cp <= 0x7E) ||
			(uni_cp >= 0x09 && uni_cp <= 0x0C && uni_cp != 0x0B) || /* form feed U+0C allowed, but not U+0D */
			(uni_cp >= 0xA0 && uni_cp <= 0x10FFFF &&
				((uni_cp & 0xFFFF) < 0xFFFE) && /* last two of each plane (nonchars) disallowed */
				(uni_cp < 0xFDD0 || uni_cp > 0xFDEF)); /* U+FDD0-U+FDEF (nonchars) disallowed */
	case ENT_HTML_DOC_XHTML:
	case ENT_HTML_DOC_XML1:
		/* OTOH, XML 1.0 requires "character references to match the production for Char
		 * See <http://www.w3.org/TR/REC-xml/#NT-CharRef> */
		return unicode_cp_is_allowed(uni_cp, document_type);
	default:
		return 1;
	}
}