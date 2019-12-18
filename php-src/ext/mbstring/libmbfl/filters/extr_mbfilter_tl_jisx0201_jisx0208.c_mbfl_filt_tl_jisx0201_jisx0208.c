#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; } ;
typedef  TYPE_1__ mbfl_filt_tl_jisx0201_jisx0208_param ;
struct TYPE_5__ {int status; int cache; int (* output_function ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; scalar_t__ opaque; } ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 int MBFL_FILT_TL_HAN2ZEN_ALL ; 
 int MBFL_FILT_TL_HAN2ZEN_ALPHA ; 
 int MBFL_FILT_TL_HAN2ZEN_COMPAT1 ; 
 int MBFL_FILT_TL_HAN2ZEN_COMPAT2 ; 
 int MBFL_FILT_TL_HAN2ZEN_GLUE ; 
 int MBFL_FILT_TL_HAN2ZEN_HIRAGANA ; 
 int MBFL_FILT_TL_HAN2ZEN_KATAKANA ; 
 int MBFL_FILT_TL_HAN2ZEN_NUMERIC ; 
 int MBFL_FILT_TL_HAN2ZEN_SPACE ; 
 int MBFL_FILT_TL_ZEN2HAN_COMPAT1 ; 
 int MBFL_FILT_TL_ZEN2HAN_COMPAT2 ; 
 int MBFL_FILT_TL_ZEN2HAN_HIRA2KANA ; 
 int MBFL_FILT_TL_ZEN2HAN_HIRAGANA ; 
 int MBFL_FILT_TL_ZEN2HAN_KANA2HIRA ; 
 int MBFL_FILT_TL_ZEN2HAN_KATAKANA ; 
 int* hankana2zenhira_table ; 
 int* hankana2zenkana_table ; 
 int stub1 (int,int /*<<< orphan*/ ) ; 
 int stub2 (int,int /*<<< orphan*/ ) ; 
 int stub3 (int,int /*<<< orphan*/ ) ; 
 int stub4 (int,int /*<<< orphan*/ ) ; 
 int stub5 (int,int /*<<< orphan*/ ) ; 
 int** zenkana2hankana_table ; 

int
mbfl_filt_tl_jisx0201_jisx0208(int c, mbfl_convert_filter *filt)
{
	int s, n;
	int mode = ((mbfl_filt_tl_jisx0201_jisx0208_param *)filt->opaque)->mode;

	s = c;

	if ((mode & MBFL_FILT_TL_HAN2ZEN_ALL)
			&& c >= 0x21 && c <= 0x7d && c != 0x22 && c != 0x27 && c != 0x5c) {
		/* all except <"> <'> <\> <~> */
		s = c + 0xfee0;
	} else if ((mode & MBFL_FILT_TL_HAN2ZEN_ALPHA) &&
			((c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a))) {
		/* alpha */
		s = c + 0xfee0;
	} else if ((mode & MBFL_FILT_TL_HAN2ZEN_NUMERIC) &&
			c >= 0x30 && c <= 0x39) {
		/* num */
		s = c + 0xfee0;
	} else if ((mode & MBFL_FILT_TL_HAN2ZEN_SPACE) && c == 0x20) {
		/* space */
		s = 0x3000;
	}

	if (mode &
			(MBFL_FILT_TL_HAN2ZEN_KATAKANA | MBFL_FILT_TL_HAN2ZEN_HIRAGANA)) {
		/* hankaku kana to zenkaku kana */
		if ((mode & MBFL_FILT_TL_HAN2ZEN_KATAKANA) &&
				(mode & MBFL_FILT_TL_HAN2ZEN_GLUE)) {
			/* hankaku kana to zenkaku katakana and glue voiced sound mark */
			if (c >= 0xff61 && c <= 0xff9f) {
				if (filt->status) {
					n = (filt->cache - 0xff60) & 0x3f;
					if (c == 0xff9e && ((n >= 22 && n <= 36) || (n >= 42 && n <= 46))) {
						filt->status = 0;
						s = 0x3001 + hankana2zenkana_table[n];
					} else if (c == 0xff9e && n == 19) {
						filt->status = 0;
						s = 0x30f4;
					} else if (c == 0xff9f && (n >= 42 && n <= 46)) {
						filt->status = 0;
						s = 0x3002 + hankana2zenkana_table[n];
					} else {
						filt->status = 1;
						filt->cache = c;
						s = 0x3000 + hankana2zenkana_table[n];
					}
				} else {
					filt->status = 1;
					filt->cache = c;
					return c;
				}
			} else {
				if (filt->status) {
					n = (filt->cache - 0xff60) & 0x3f;
					filt->status = 0;
					(*filt->output_function)(0x3000 + hankana2zenkana_table[n], filt->data);
				}
			}
		} else if ((mode & MBFL_FILT_TL_HAN2ZEN_HIRAGANA) &&
				(mode & MBFL_FILT_TL_HAN2ZEN_GLUE)) {
			/* hankaku kana to zenkaku hirangana and glue voiced sound mark */
			if (c >= 0xff61 && c <= 0xff9f) {
				if (filt->status) {
					n = (filt->cache - 0xff60) & 0x3f;
					if (c == 0xff9e && ((n >= 22 && n <= 36) || (n >= 42 && n <= 46))) {
						filt->status = 0;
						s = 0x3001 + hankana2zenhira_table[n];
					} else if (c == 0xff9f && (n >= 42 && n <= 46)) {
						filt->status = 0;
						s = 0x3002 + hankana2zenhira_table[n];
					} else {
						filt->status = 1;
						filt->cache = c;
						s = 0x3000 + hankana2zenhira_table[n];
					}
				} else {
					filt->status = 1;
					filt->cache = c;
					return c;
				}
			} else {
				if (filt->status) {
					n = (filt->cache - 0xff60) & 0x3f;
					filt->status = 0;
					(*filt->output_function)(0x3000 + hankana2zenhira_table[n], filt->data);
				}
			}
		} else if ((mode & MBFL_FILT_TL_HAN2ZEN_KATAKANA) &&
				c >= 0xff61 && c <= 0xff9f) {
			/* hankaku kana to zenkaku katakana */
			s = 0x3000 + hankana2zenkana_table[c - 0xff60];
		} else if ((mode & MBFL_FILT_TL_HAN2ZEN_HIRAGANA)
				&& c >= 0xff61 && c <= 0xff9f) {
			/* hankaku kana to zenkaku hirangana */
			s = 0x3000 + hankana2zenhira_table[c - 0xff60];
		}
	}

	if (mode & MBFL_FILT_TL_HAN2ZEN_COMPAT1) {
		/* special ascii to symbol */
		if (c == 0x5c) {
			s = 0xffe5;				/* FULLWIDTH YEN SIGN */
		} else if (c == 0xa5) {		/* YEN SIGN */
			s = 0xffe5;				/* FULLWIDTH YEN SIGN */
		} else if (c == 0x7e) {
			s = 0xffe3;				/* FULLWIDTH MACRON */
		} else if (c == 0x203e) {	/* OVERLINE */
			s = 0xffe3;				/* FULLWIDTH MACRON */
		} else if (c == 0x27) {
			s = 0x2019;				/* RIGHT SINGLE QUOTATION MARK */
		} else if (c == 0x22) {
			s = 0x201d;				/* RIGHT DOUBLE QUOTATION MARK */
		}
	} else if (mode & MBFL_FILT_TL_HAN2ZEN_COMPAT2) {
		/* special ascii to symbol */
		if (c == 0x5c) {
			s = 0xff3c;				/* FULLWIDTH REVERSE SOLIDUS */
		} else if (c == 0x7e) {
			s = 0xff5e;				/* FULLWIDTH TILDE */
		} else if (c == 0x27) {
			s = 0xff07;				/* FULLWIDTH APOSTROPHE */
		} else if (c == 0x22) {
			s = 0xff02;				/* FULLWIDTH QUOTATION MARK */
		}
	}

	if (mode & 0xf0) { /* zenkaku to hankaku */
		if ((mode & 0x10) && c >= 0xff01 && c <= 0xff5d && c != 0xff02 && c != 0xff07 && c!= 0xff3c) {	/* all except <"> <'> <\> <~> */
			s = c - 0xfee0;
		} else if ((mode & 0x20) && ((c >= 0xff21 && c <= 0xff3a) || (c >= 0xff41 && c <= 0xff5a))) {	/* alpha */
			s = c - 0xfee0;
		} else if ((mode & 0x40) && (c >= 0xff10 && c <= 0xff19)) {	/* num */
			s = c - 0xfee0;
		} else if ((mode & 0x80) && (c == 0x3000)) {	/* spase */
			s = 0x20;
		} else if ((mode & 0x10) && (c == 0x2212)) {	/* MINUS SIGN */
			s = 0x2d;
		}
	}

	if (mode &
			(MBFL_FILT_TL_ZEN2HAN_KATAKANA | MBFL_FILT_TL_ZEN2HAN_HIRAGANA)) {
		/* Zenkaku kana to hankaku kana */
		if ((mode & MBFL_FILT_TL_ZEN2HAN_KATAKANA) &&
				c >= 0x30a1 && c <= 0x30f4) {
			/* Zenkaku katakana to hankaku kana */
			n = c - 0x30a1;
			if (zenkana2hankana_table[n][1] != 0) {
				(filt->output_function)(0xff00 + zenkana2hankana_table[n][0], filt->data);
				s = 0xff00 + zenkana2hankana_table[n][1];
			} else {
				s = 0xff00 + zenkana2hankana_table[n][0];
			}
		} else if ((mode & MBFL_FILT_TL_ZEN2HAN_HIRAGANA) &&
				c >= 0x3041 && c <= 0x3093) {
			/* Zenkaku hirangana to hankaku kana */
			n = c - 0x3041;
			if (zenkana2hankana_table[n][1] != 0) {
				(filt->output_function)(0xff00 + zenkana2hankana_table[n][0], filt->data);
				s = 0xff00 + zenkana2hankana_table[n][1];
			} else {
				s = 0xff00 + zenkana2hankana_table[n][0];
			}
		} else if (c == 0x3001) {
			s = 0xff64;				/* HALFWIDTH IDEOGRAPHIC COMMA */
		} else if (c == 0x3002) {
			s = 0xff61;				/* HALFWIDTH IDEOGRAPHIC FULL STOP */
		} else if (c == 0x300c) {
			s = 0xff62;				/* HALFWIDTH LEFT CORNER BRACKET */
		} else if (c == 0x300d) {
			s = 0xff63;				/* HALFWIDTH RIGHT CORNER BRACKET */
		} else if (c == 0x309b) {
			s = 0xff9e;				/* HALFWIDTH KATAKANA VOICED SOUND MARK */
		} else if (c == 0x309c) {
			s = 0xff9f;				/* HALFWIDTH KATAKANA SEMI-VOICED SOUND MARK */
		} else if (c == 0x30fc) {
			s = 0xff70;				/* HALFWIDTH KATAKANA-HIRAGANA PROLONGED SOUND MARK */
		} else if (c == 0x30fb) {
			s = 0xff65;				/* HALFWIDTH KATAKANA MIDDLE DOT */
		}
	} else if (mode & (MBFL_FILT_TL_ZEN2HAN_HIRA2KANA
			| MBFL_FILT_TL_ZEN2HAN_KANA2HIRA)) {
		if ((mode & MBFL_FILT_TL_ZEN2HAN_HIRA2KANA) &&
				((c >= 0x3041 && c <= 0x3093) || c == 0x309d || c == 0x309e)) {
			/* Zenkaku hirangana to Zenkaku katakana */
			s = c + 0x60;
		} else if ((mode & MBFL_FILT_TL_ZEN2HAN_KANA2HIRA) &&
				((c >= 0x30a1 && c <= 0x30f3) || c == 0x30fd || c == 0x30fe)) {
			/* Zenkaku katakana to Zenkaku hirangana */
			s = c - 0x60;
		}
	}

	if (mode & MBFL_FILT_TL_ZEN2HAN_COMPAT1) {	/* special symbol to ascii */
		if (c == 0xffe5) {			/* FULLWIDTH YEN SIGN */
			s = 0x5c;
		} else if (c == 0xff3c) {	/* FULLWIDTH REVERSE SOLIDUS */
			s = 0x5c;
		} else if (c == 0xffe3) {	/* FULLWIDTH MACRON */
			s = 0x7e;
		} else if (c == 0x203e) {	/* OVERLINE */
			s = 0x7e;
		} else if (c == 0x2018) {	/* LEFT SINGLE QUOTATION MARK*/
			s = 0x27;
		} else if (c == 0x2019) {	/* RIGHT SINGLE QUOTATION MARK */
			s = 0x27;
		} else if (c == 0x201c) {	/* LEFT DOUBLE QUOTATION MARK */
			s = 0x22;
		} else if (c == 0x201d) {	/* RIGHT DOUBLE QUOTATION MARK */
			s = 0x22;
		}
	}

	if (mode & MBFL_FILT_TL_ZEN2HAN_COMPAT2) {	/* special symbol to ascii */
		if (c == 0xff3c) {			/* FULLWIDTH REVERSE SOLIDUS */
			s = 0x5c;
		} else if (c == 0xff5e) {	/* FULLWIDTH TILDE */
			s = 0x7e;
		} else if (c == 0xff07) {	/* FULLWIDTH APOSTROPHE */
			s = 0x27;
		} else if (c == 0xff02) {	/* FULLWIDTH QUOTATION MARK */
			s = 0x22;
		}
	}

	return (*filt->output_function)(s, filt->data);
}