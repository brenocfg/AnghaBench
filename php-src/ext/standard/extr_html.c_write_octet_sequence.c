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
typedef  enum entity_charset { ____Placeholder_entity_charset } entity_charset ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
#define  cs_8859_1 141 
#define  cs_8859_15 140 
#define  cs_8859_5 139 
#define  cs_big5 138 
#define  cs_big5hkscs 137 
#define  cs_cp1251 136 
#define  cs_cp1252 135 
#define  cs_cp866 134 
#define  cs_eucjp 133 
#define  cs_gb2312 132 
#define  cs_koi8r 131 
#define  cs_macroman 130 
#define  cs_sjis 129 
#define  cs_utf_8 128 
 size_t php_mb2_int_to_char (unsigned char*,unsigned int) ; 
 size_t php_utf32_utf8 (unsigned char*,unsigned int) ; 

__attribute__((used)) static inline size_t write_octet_sequence(unsigned char *buf, enum entity_charset charset, unsigned code) {
	/* code is not necessarily a unicode code point */
	switch (charset) {
	case cs_utf_8:
		return php_utf32_utf8(buf, code);

	case cs_8859_1:
	case cs_cp1252:
	case cs_8859_15:
	case cs_koi8r:
	case cs_cp1251:
	case cs_8859_5:
	case cs_cp866:
	case cs_macroman:
		/* single byte stuff */
		*buf = code;
		return 1;

	case cs_big5:
	case cs_big5hkscs:
	case cs_sjis:
	case cs_gb2312:
		/* we don't have complete unicode mappings for these yet in entity_decode,
		 * and we opt to pass through the octet sequences for these in htmlentities
		 * instead of converting to an int and then converting back. */
#if 0
		return php_mb2_int_to_char(buf, code);
#else
#if ZEND_DEBUG
		assert(code <= 0xFFU);
#endif
		*buf = code;
		return 1;
#endif

	case cs_eucjp:
#if 0 /* idem */
		return php_mb2_int_to_char(buf, code);
#else
#if ZEND_DEBUG
		assert(code <= 0xFFU);
#endif
		*buf = code;
		return 1;
#endif

	default:
		assert(0);
		return 0;
	}
}