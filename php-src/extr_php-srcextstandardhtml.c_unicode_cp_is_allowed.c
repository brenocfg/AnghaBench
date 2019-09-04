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

__attribute__((used)) static inline int unicode_cp_is_allowed(unsigned uni_cp, int document_type)
{
	/* XML 1.0				HTML 4.01			HTML 5
	 * 0x09..0x0A			0x09..0x0A			0x09..0x0A
	 * 0x0D					0x0D				0x0C..0x0D
	 * 0x0020..0xD7FF		0x20..0x7E			0x20..0x7E
	 *						0x00A0..0xD7FF		0x00A0..0xD7FF
	 * 0xE000..0xFFFD		0xE000..0x10FFFF	0xE000..0xFDCF
	 * 0x010000..0x10FFFF						0xFDF0..0x10FFFF (*)
	 *
	 * (*) exclude code points where ((code & 0xFFFF) >= 0xFFFE)
	 *
	 * References:
	 * XML 1.0:   <http://www.w3.org/TR/REC-xml/#charsets>
	 * HTML 4.01: <http://www.w3.org/TR/1999/PR-html40-19990824/sgml/sgmldecl.html>
	 * HTML 5:    <http://dev.w3.org/html5/spec/Overview.html#preprocessing-the-input-stream>
	 *
	 * Not sure this is the relevant part for HTML 5, though. I opted to
	 * disallow the characters that would result in a parse error when
	 * preprocessing of the input stream. See also section 8.1.3.
	 *
	 * It's unclear if XHTML 1.0 allows C1 characters. I'll opt to apply to
	 * XHTML 1.0 the same rules as for XML 1.0.
	 * See <http://cmsmcq.com/2007/C1.xml>.
	 */

	switch (document_type) {
	case ENT_HTML_DOC_HTML401:
		return (uni_cp >= 0x20 && uni_cp <= 0x7E) ||
			(uni_cp == 0x0A || uni_cp == 0x09 || uni_cp == 0x0D) ||
			(uni_cp >= 0xA0 && uni_cp <= 0xD7FF) ||
			(uni_cp >= 0xE000 && uni_cp <= 0x10FFFF);
	case ENT_HTML_DOC_HTML5:
		return (uni_cp >= 0x20 && uni_cp <= 0x7E) ||
			(uni_cp >= 0x09 && uni_cp <= 0x0D && uni_cp != 0x0B) || /* form feed U+0C allowed */
			(uni_cp >= 0xA0 && uni_cp <= 0xD7FF) ||
			(uni_cp >= 0xE000 && uni_cp <= 0x10FFFF &&
				((uni_cp & 0xFFFF) < 0xFFFE) && /* last two of each plane (nonchars) disallowed */
				(uni_cp < 0xFDD0 || uni_cp > 0xFDEF)); /* U+FDD0-U+FDEF (nonchars) disallowed */
	case ENT_HTML_DOC_XHTML:
	case ENT_HTML_DOC_XML1:
		return (uni_cp >= 0x20 && uni_cp <= 0xD7FF) ||
			(uni_cp == 0x0A || uni_cp == 0x09 || uni_cp == 0x0D) ||
			(uni_cp >= 0xE000 && uni_cp <= 0x10FFFF && uni_cp != 0xFFFE && uni_cp != 0xFFFF);
	default:
		return 1;
	}
}