#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {unsigned int ignore; int state; unsigned int* string; int nextstate; unsigned int quote; scalar_t__ byte; int /*<<< orphan*/  line; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_state_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;

/* Variables and functions */
#define  YXMLS_attr0 193 
#define  YXMLS_attr1 192 
#define  YXMLS_attr2 191 
#define  YXMLS_attr3 190 
#define  YXMLS_attr4 189 
#define  YXMLS_cd0 188 
#define  YXMLS_cd1 187 
#define  YXMLS_cd2 186 
#define  YXMLS_comment0 185 
#define  YXMLS_comment1 184 
#define  YXMLS_comment2 183 
#define  YXMLS_comment3 182 
#define  YXMLS_comment4 181 
#define  YXMLS_dt0 180 
#define  YXMLS_dt1 179 
#define  YXMLS_dt2 178 
#define  YXMLS_dt3 177 
#define  YXMLS_dt4 176 
#define  YXMLS_elem0 175 
#define  YXMLS_elem1 174 
#define  YXMLS_elem2 173 
#define  YXMLS_elem3 172 
#define  YXMLS_enc0 171 
#define  YXMLS_enc1 170 
#define  YXMLS_enc2 169 
#define  YXMLS_enc3 168 
#define  YXMLS_etag0 167 
#define  YXMLS_etag1 166 
#define  YXMLS_etag2 165 
#define  YXMLS_init 164 
#define  YXMLS_le0 163 
#define  YXMLS_le1 162 
#define  YXMLS_le2 161 
#define  YXMLS_le3 160 
#define  YXMLS_lee1 159 
#define  YXMLS_lee2 158 
#define  YXMLS_leq0 157 
#define  YXMLS_misc0 156 
#define  YXMLS_misc1 155 
#define  YXMLS_misc2 154 
#define  YXMLS_misc2a 153 
#define  YXMLS_misc3 152 
#define  YXMLS_pi0 151 
#define  YXMLS_pi1 150 
#define  YXMLS_pi2 149 
#define  YXMLS_pi3 148 
#define  YXMLS_pi4 147 
#define  YXMLS_std0 146 
#define  YXMLS_std1 145 
#define  YXMLS_std2 144 
#define  YXMLS_std3 143 
#define  YXMLS_string 142 
#define  YXMLS_ver0 141 
#define  YXMLS_ver1 140 
#define  YXMLS_ver2 139 
#define  YXMLS_ver3 138 
#define  YXMLS_xmldecl0 137 
#define  YXMLS_xmldecl1 136 
#define  YXMLS_xmldecl2 135 
#define  YXMLS_xmldecl3 134 
#define  YXMLS_xmldecl4 133 
#define  YXMLS_xmldecl5 132 
#define  YXMLS_xmldecl6 131 
#define  YXMLS_xmldecl7 130 
#define  YXMLS_xmldecl8 129 
#define  YXMLS_xmldecl9 128 
 int /*<<< orphan*/  YXML_ESYN ; 
 int /*<<< orphan*/  YXML_OK ; 
 int /*<<< orphan*/  yxml_attrname (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_attrnameend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_attrstart (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_attrvalend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_dataattr (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_datacd1 (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_datacd2 (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_datacontent (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_datapi1 (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_datapi2 (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_elemclose (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_elemcloseend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_elemname (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_elemnameend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_elemstart (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_isAlpha (unsigned int) ; 
 int /*<<< orphan*/  yxml_isAttValue (unsigned int) ; 
 int /*<<< orphan*/  yxml_isChar (unsigned int) ; 
 int /*<<< orphan*/  yxml_isEncName (unsigned int) ; 
 int /*<<< orphan*/  yxml_isName (unsigned int) ; 
 int /*<<< orphan*/  yxml_isNameStart (unsigned int) ; 
 int /*<<< orphan*/  yxml_isNum (unsigned int) ; 
 int /*<<< orphan*/  yxml_isRef (unsigned int) ; 
 int /*<<< orphan*/  yxml_isSP (unsigned int) ; 
 int /*<<< orphan*/  yxml_piabort (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_piname (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_pinameend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_pistart (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_pivalend (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_ref (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_refattrval (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_refcontent (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_refstart (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  yxml_selfclose (TYPE_1__*,unsigned int) ; 

yxml_ret_t yxml_parse(yxml_t *x, int _ch) {
	/* Ensure that characters are in the range of 0..255 rather than -126..125.
	 * All character comparisons are done with positive integers. */
	unsigned ch = (unsigned)(_ch+256) & 0xff;
	if(!ch)
		return YXML_ESYN;
	x->total++;

	/* End-of-Line normalization, "\rX", "\r\n" and "\n" are recognized and
	 * normalized to a single '\n' as per XML 1.0 section 2.11. XML 1.1 adds
	 * some non-ASCII character sequences to this list, but we can only handle
	 * ASCII here without making assumptions about the input encoding. */
	if(x->ignore == ch) {
		x->ignore = 0;
		return YXML_OK;
	}
	x->ignore = (ch == 0xd) * 0xa;
	if(ch == 0xa || ch == 0xd) {
		ch = 0xa;
		x->line++;
		x->byte = 0;
	}
	x->byte++;

	switch((yxml_state_t)x->state) {
	case YXMLS_string:
		if(ch == *x->string) {
			x->string++;
			if(!*x->string)
				x->state = x->nextstate;
			return YXML_OK;
		}
		break;
	case YXMLS_attr0:
		if(yxml_isName(ch))
			return yxml_attrname(x, ch);
		if(yxml_isSP(ch)) {
			x->state = YXMLS_attr1;
			return yxml_attrnameend(x, ch);
		}
		if(ch == (unsigned char)'=') {
			x->state = YXMLS_attr2;
			return yxml_attrnameend(x, ch);
		}
		break;
	case YXMLS_attr1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'=') {
			x->state = YXMLS_attr2;
			return YXML_OK;
		}
		break;
	case YXMLS_attr2:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_attr3;
			x->quote = ch;
			return YXML_OK;
		}
		break;
	case YXMLS_attr3:
		if(yxml_isAttValue(ch))
			return yxml_dataattr(x, ch);
		if(ch == (unsigned char)'&') {
			x->state = YXMLS_attr4;
			return yxml_refstart(x, ch);
		}
		if(x->quote == ch) {
			x->state = YXMLS_elem2;
			return yxml_attrvalend(x, ch);
		}
		break;
	case YXMLS_attr4:
		if(yxml_isRef(ch))
			return yxml_ref(x, ch);
		if(ch == (unsigned char)'\x3b') {
			x->state = YXMLS_attr3;
			return yxml_refattrval(x, ch);
		}
		break;
	case YXMLS_cd0:
		if(ch == (unsigned char)']') {
			x->state = YXMLS_cd1;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return yxml_datacontent(x, ch);
		break;
	case YXMLS_cd1:
		if(ch == (unsigned char)']') {
			x->state = YXMLS_cd2;
			return YXML_OK;
		}
		if(yxml_isChar(ch)) {
			x->state = YXMLS_cd0;
			return yxml_datacd1(x, ch);
		}
		break;
	case YXMLS_cd2:
		if(ch == (unsigned char)']')
			return yxml_datacontent(x, ch);
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return YXML_OK;
		}
		if(yxml_isChar(ch)) {
			x->state = YXMLS_cd0;
			return yxml_datacd2(x, ch);
		}
		break;
	case YXMLS_comment0:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment1;
			return YXML_OK;
		}
		break;
	case YXMLS_comment1:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment2;
			return YXML_OK;
		}
		break;
	case YXMLS_comment2:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment3;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return YXML_OK;
		break;
	case YXMLS_comment3:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment4;
			return YXML_OK;
		}
		if(yxml_isChar(ch)) {
			x->state = YXMLS_comment2;
			return YXML_OK;
		}
		break;
	case YXMLS_comment4:
		if(ch == (unsigned char)'>') {
			x->state = x->nextstate;
			return YXML_OK;
		}
		break;
	case YXMLS_dt0:
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc1;
			return YXML_OK;
		}
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_dt1;
			x->quote = ch;
			x->nextstate = YXMLS_dt0;
			return YXML_OK;
		}
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_dt2;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return YXML_OK;
		break;
	case YXMLS_dt1:
		if(x->quote == ch) {
			x->state = x->nextstate;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return YXML_OK;
		break;
	case YXMLS_dt2:
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi0;
			x->nextstate = YXMLS_dt0;
			return YXML_OK;
		}
		if(ch == (unsigned char)'!') {
			x->state = YXMLS_dt3;
			return YXML_OK;
		}
		break;
	case YXMLS_dt3:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment1;
			x->nextstate = YXMLS_dt0;
			return YXML_OK;
		}
		if(yxml_isChar(ch)) {
			x->state = YXMLS_dt4;
			return YXML_OK;
		}
		break;
	case YXMLS_dt4:
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_dt1;
			x->quote = ch;
			x->nextstate = YXMLS_dt4;
			return YXML_OK;
		}
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_dt0;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return YXML_OK;
		break;
	case YXMLS_elem0:
		if(yxml_isName(ch))
			return yxml_elemname(x, ch);
		if(yxml_isSP(ch)) {
			x->state = YXMLS_elem1;
			return yxml_elemnameend(x, ch);
		}
		if(ch == (unsigned char)'/') {
			x->state = YXMLS_elem3;
			return yxml_elemnameend(x, ch);
		}
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return yxml_elemnameend(x, ch);
		}
		break;
	case YXMLS_elem1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'/') {
			x->state = YXMLS_elem3;
			return YXML_OK;
		}
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return YXML_OK;
		}
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_attr0;
			return yxml_attrstart(x, ch);
		}
		break;
	case YXMLS_elem2:
		if(yxml_isSP(ch)) {
			x->state = YXMLS_elem1;
			return YXML_OK;
		}
		if(ch == (unsigned char)'/') {
			x->state = YXMLS_elem3;
			return YXML_OK;
		}
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return YXML_OK;
		}
		break;
	case YXMLS_elem3:
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return yxml_selfclose(x, ch);
		}
		break;
	case YXMLS_enc0:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'=') {
			x->state = YXMLS_enc1;
			return YXML_OK;
		}
		break;
	case YXMLS_enc1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_enc2;
			x->quote = ch;
			return YXML_OK;
		}
		break;
	case YXMLS_enc2:
		if(yxml_isAlpha(ch)) {
			x->state = YXMLS_enc3;
			return YXML_OK;
		}
		break;
	case YXMLS_enc3:
		if(yxml_isEncName(ch))
			return YXML_OK;
		if(x->quote == ch) {
			x->state = YXMLS_xmldecl6;
			return YXML_OK;
		}
		break;
	case YXMLS_etag0:
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_etag1;
			return yxml_elemclose(x, ch);
		}
		break;
	case YXMLS_etag1:
		if(yxml_isName(ch))
			return yxml_elemclose(x, ch);
		if(yxml_isSP(ch)) {
			x->state = YXMLS_etag2;
			return yxml_elemcloseend(x, ch);
		}
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return yxml_elemcloseend(x, ch);
		}
		break;
	case YXMLS_etag2:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc2;
			return YXML_OK;
		}
		break;
	case YXMLS_init:
		if(ch == (unsigned char)'\xef') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_misc0;
			x->string = (unsigned char *)"\xbb\xbf";
			return YXML_OK;
		}
		if(yxml_isSP(ch)) {
			x->state = YXMLS_misc0;
			return YXML_OK;
		}
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_le0;
			return YXML_OK;
		}
		break;
	case YXMLS_le0:
		if(ch == (unsigned char)'!') {
			x->state = YXMLS_lee1;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_leq0;
			return YXML_OK;
		}
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_elem0;
			return yxml_elemstart(x, ch);
		}
		break;
	case YXMLS_le1:
		if(ch == (unsigned char)'!') {
			x->state = YXMLS_lee1;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi0;
			x->nextstate = YXMLS_misc1;
			return YXML_OK;
		}
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_elem0;
			return yxml_elemstart(x, ch);
		}
		break;
	case YXMLS_le2:
		if(ch == (unsigned char)'!') {
			x->state = YXMLS_lee2;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi0;
			x->nextstate = YXMLS_misc2;
			return YXML_OK;
		}
		if(ch == (unsigned char)'/') {
			x->state = YXMLS_etag0;
			return YXML_OK;
		}
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_elem0;
			return yxml_elemstart(x, ch);
		}
		break;
	case YXMLS_le3:
		if(ch == (unsigned char)'!') {
			x->state = YXMLS_comment0;
			x->nextstate = YXMLS_misc3;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi0;
			x->nextstate = YXMLS_misc3;
			return YXML_OK;
		}
		break;
	case YXMLS_lee1:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment1;
			x->nextstate = YXMLS_misc1;
			return YXML_OK;
		}
		if(ch == (unsigned char)'D') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_dt0;
			x->string = (unsigned char *)"OCTYPE";
			return YXML_OK;
		}
		break;
	case YXMLS_lee2:
		if(ch == (unsigned char)'-') {
			x->state = YXMLS_comment1;
			x->nextstate = YXMLS_misc2;
			return YXML_OK;
		}
		if(ch == (unsigned char)'[') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_cd0;
			x->string = (unsigned char *)"CDATA[";
			return YXML_OK;
		}
		break;
	case YXMLS_leq0:
		if(ch == (unsigned char)'x') {
			x->state = YXMLS_xmldecl0;
			x->nextstate = YXMLS_misc1;
			return yxml_pistart(x, ch);
		}
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_pi1;
			x->nextstate = YXMLS_misc1;
			return yxml_pistart(x, ch);
		}
		break;
	case YXMLS_misc0:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_le0;
			return YXML_OK;
		}
		break;
	case YXMLS_misc1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_le1;
			return YXML_OK;
		}
		break;
	case YXMLS_misc2:
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_le2;
			return YXML_OK;
		}
		if(ch == (unsigned char)'&') {
			x->state = YXMLS_misc2a;
			return yxml_refstart(x, ch);
		}
		if(yxml_isChar(ch))
			return yxml_datacontent(x, ch);
		break;
	case YXMLS_misc2a:
		if(yxml_isRef(ch))
			return yxml_ref(x, ch);
		if(ch == (unsigned char)'\x3b') {
			x->state = YXMLS_misc2;
			return yxml_refcontent(x, ch);
		}
		break;
	case YXMLS_misc3:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'<') {
			x->state = YXMLS_le3;
			return YXML_OK;
		}
		break;
	case YXMLS_pi0:
		if(yxml_isNameStart(ch)) {
			x->state = YXMLS_pi1;
			return yxml_pistart(x, ch);
		}
		break;
	case YXMLS_pi1:
		if(yxml_isName(ch))
			return yxml_piname(x, ch);
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi4;
			return yxml_pinameend(x, ch);
		}
		if(yxml_isSP(ch)) {
			x->state = YXMLS_pi2;
			return yxml_pinameend(x, ch);
		}
		break;
	case YXMLS_pi2:
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi3;
			return YXML_OK;
		}
		if(yxml_isChar(ch))
			return yxml_datapi1(x, ch);
		break;
	case YXMLS_pi3:
		if(ch == (unsigned char)'>') {
			x->state = x->nextstate;
			return yxml_pivalend(x, ch);
		}
		if(yxml_isChar(ch)) {
			x->state = YXMLS_pi2;
			return yxml_datapi2(x, ch);
		}
		break;
	case YXMLS_pi4:
		if(ch == (unsigned char)'>') {
			x->state = x->nextstate;
			return yxml_pivalend(x, ch);
		}
		break;
	case YXMLS_std0:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'=') {
			x->state = YXMLS_std1;
			return YXML_OK;
		}
		break;
	case YXMLS_std1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_std2;
			x->quote = ch;
			return YXML_OK;
		}
		break;
	case YXMLS_std2:
		if(ch == (unsigned char)'y') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_std3;
			x->string = (unsigned char *)"es";
			return YXML_OK;
		}
		if(ch == (unsigned char)'n') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_std3;
			x->string = (unsigned char *)"o";
			return YXML_OK;
		}
		break;
	case YXMLS_std3:
		if(x->quote == ch) {
			x->state = YXMLS_xmldecl8;
			return YXML_OK;
		}
		break;
	case YXMLS_ver0:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'=') {
			x->state = YXMLS_ver1;
			return YXML_OK;
		}
		break;
	case YXMLS_ver1:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'\'' || ch == (unsigned char)'"') {
			x->state = YXMLS_string;
			x->quote = ch;
			x->nextstate = YXMLS_ver2;
			x->string = (unsigned char *)"1.";
			return YXML_OK;
		}
		break;
	case YXMLS_ver2:
		if(yxml_isNum(ch)) {
			x->state = YXMLS_ver3;
			return YXML_OK;
		}
		break;
	case YXMLS_ver3:
		if(yxml_isNum(ch))
			return YXML_OK;
		if(x->quote == ch) {
			x->state = YXMLS_xmldecl4;
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl0:
		if(ch == (unsigned char)'m') {
			x->state = YXMLS_xmldecl1;
			return yxml_piname(x, ch);
		}
		if(yxml_isName(ch)) {
			x->state = YXMLS_pi1;
			return yxml_piname(x, ch);
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi4;
			return yxml_pinameend(x, ch);
		}
		if(yxml_isSP(ch)) {
			x->state = YXMLS_pi2;
			return yxml_pinameend(x, ch);
		}
		break;
	case YXMLS_xmldecl1:
		if(ch == (unsigned char)'l') {
			x->state = YXMLS_xmldecl2;
			return yxml_piname(x, ch);
		}
		if(yxml_isName(ch)) {
			x->state = YXMLS_pi1;
			return yxml_piname(x, ch);
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_pi4;
			return yxml_pinameend(x, ch);
		}
		if(yxml_isSP(ch)) {
			x->state = YXMLS_pi2;
			return yxml_pinameend(x, ch);
		}
		break;
	case YXMLS_xmldecl2:
		if(yxml_isSP(ch)) {
			x->state = YXMLS_xmldecl3;
			return yxml_piabort(x, ch);
		}
		if(yxml_isName(ch)) {
			x->state = YXMLS_pi1;
			return yxml_piname(x, ch);
		}
		break;
	case YXMLS_xmldecl3:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'v') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_ver0;
			x->string = (unsigned char *)"ersion";
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl4:
		if(yxml_isSP(ch)) {
			x->state = YXMLS_xmldecl5;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_xmldecl9;
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl5:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_xmldecl9;
			return YXML_OK;
		}
		if(ch == (unsigned char)'e') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_enc0;
			x->string = (unsigned char *)"ncoding";
			return YXML_OK;
		}
		if(ch == (unsigned char)'s') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_std0;
			x->string = (unsigned char *)"tandalone";
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl6:
		if(yxml_isSP(ch)) {
			x->state = YXMLS_xmldecl7;
			return YXML_OK;
		}
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_xmldecl9;
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl7:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_xmldecl9;
			return YXML_OK;
		}
		if(ch == (unsigned char)'s') {
			x->state = YXMLS_string;
			x->nextstate = YXMLS_std0;
			x->string = (unsigned char *)"tandalone";
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl8:
		if(yxml_isSP(ch))
			return YXML_OK;
		if(ch == (unsigned char)'?') {
			x->state = YXMLS_xmldecl9;
			return YXML_OK;
		}
		break;
	case YXMLS_xmldecl9:
		if(ch == (unsigned char)'>') {
			x->state = YXMLS_misc1;
			return YXML_OK;
		}
		break;
	}
	return YXML_ESYN;
}