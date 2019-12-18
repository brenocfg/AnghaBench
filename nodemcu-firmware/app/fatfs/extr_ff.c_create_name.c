#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {TYPE_1__* fs; } ;
struct TYPE_7__ {char* fn; TYPE_2__ obj; } ;
struct TYPE_5__ {char* lfnbuf; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  int DWORD ;
typedef  TYPE_3__ DIR ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CODEPAGE ; 
 int DDEM ; 
 void** ExCvt ; 
 int FF_MAX_LFN ; 
 int /*<<< orphan*/  FR_INVALID_NAME ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ IsLower (int) ; 
 scalar_t__ IsUpper (char) ; 
 size_t NSFLAG ; 
 int NS_BODY ; 
 int NS_DOT ; 
 int NS_EXT ; 
 int NS_LAST ; 
 int NS_LFN ; 
 int NS_LOSS ; 
 void* RDDEM ; 
 scalar_t__ chk_chr (char*,int) ; 
 scalar_t__ dbc_1st (int) ; 
 int /*<<< orphan*/  dbc_2nd (int) ; 
 char ff_uni2oem (char,int /*<<< orphan*/ ) ; 
 char ff_wtoupper (char) ; 
 int /*<<< orphan*/  mem_set (int*,char,int) ; 
 int tchar2uni (char const**) ; 

__attribute__((used)) static FRESULT create_name (	/* FR_OK: successful, FR_INVALID_NAME: could not create */
	DIR* dp,					/* Pointer to the directory object */
	const TCHAR** path			/* Pointer to pointer to the segment in the path string */
)
{
#if FF_USE_LFN		/* LFN configuration */
	BYTE b, cf;
	WCHAR wc, *lfn;
	DWORD uc;
	UINT i, ni, si, di;
	const TCHAR *p;


	/* Create LFN into LFN working buffer */
	p = *path; lfn = dp->obj.fs->lfnbuf; di = 0;
	for (;;) {
		uc = tchar2uni(&p);			/* Get a character */
		if (uc == 0xFFFFFFFF) return FR_INVALID_NAME;		/* Invalid code or UTF decode error */
		if (uc >= 0x10000) lfn[di++] = (WCHAR)(uc >> 16);	/* Store high surrogate if needed */
		wc = (WCHAR)uc;
		if (wc < ' ' || wc == '/' || wc == '\\') break;	/* Break if end of the path or a separator is found */
		if (wc < 0x80 && chk_chr("\"*:<>\?|\x7F", wc)) return FR_INVALID_NAME;	/* Reject illegal characters for LFN */
		if (di >= FF_MAX_LFN) return FR_INVALID_NAME;	/* Reject too long name */
		lfn[di++] = wc;					/* Store the Unicode character */
	}
	while (*p == '/' || *p == '\\') p++;	/* Skip duplicated separators if exist */
	*path = p;							/* Return pointer to the next segment */
	cf = (wc < ' ') ? NS_LAST : 0;		/* Set last segment flag if end of the path */

#if FF_FS_RPATH != 0
	if ((di == 1 && lfn[di - 1] == '.') ||
		(di == 2 && lfn[di - 1] == '.' && lfn[di - 2] == '.')) {	/* Is this segment a dot name? */
		lfn[di] = 0;
		for (i = 0; i < 11; i++) {		/* Create dot name for SFN entry */
			dp->fn[i] = (i < di) ? '.' : ' ';
		}
		dp->fn[i] = cf | NS_DOT;		/* This is a dot entry */
		return FR_OK;
	}
#endif
	while (di) {						/* Snip off trailing spaces and dots if exist */
		wc = lfn[di - 1];
		if (wc != ' ' && wc != '.') break;
		di--;
	}
	lfn[di] = 0;							/* LFN is created into the working buffer */
	if (di == 0) return FR_INVALID_NAME;	/* Reject null name */

	/* Create SFN in directory form */
	for (si = 0; lfn[si] == ' '; si++) ;	/* Remove leading spaces */
	if (si > 0 || lfn[si] == '.') cf |= NS_LOSS | NS_LFN;	/* Is there any leading space or dot? */
	while (di > 0 && lfn[di - 1] != '.') di--;	/* Find last dot (di<=si: no extension) */

	mem_set(dp->fn, ' ', 11);
	i = b = 0; ni = 8;
	for (;;) {
		wc = lfn[si++];					/* Get an LFN character */
		if (wc == 0) break;				/* Break on end of the LFN */
		if (wc == ' ' || (wc == '.' && si != di)) {	/* Remove embedded spaces and dots */
			cf |= NS_LOSS | NS_LFN;
			continue;
		}

		if (i >= ni || si == di) {		/* End of field? */
			if (ni == 11) {				/* Name extension overflow? */
				cf |= NS_LOSS | NS_LFN;
				break;
			}
			if (si != di) cf |= NS_LOSS | NS_LFN;	/* Name body overflow? */
			if (si > di) break;						/* No name extension? */
			si = di; i = 8; ni = 11; b <<= 2;		/* Enter name extension */
			continue;
		}

		if (wc >= 0x80) {	/* Is this a non-ASCII character? */
			cf |= NS_LFN;	/* LFN entry needs to be created */
#if FF_CODE_PAGE == 0
			if (ExCvt) {	/* At SBCS */
				wc = ff_uni2oem(wc, CODEPAGE);			/* Unicode ==> ANSI/OEM code */
				if (wc & 0x80) wc = ExCvt[wc & 0x7F];	/* Convert extended character to upper (SBCS) */
			} else {		/* At DBCS */
				wc = ff_uni2oem(ff_wtoupper(wc), CODEPAGE);	/* Unicode ==> Upper convert ==> ANSI/OEM code */
			}
#elif FF_CODE_PAGE < 900	/* SBCS cfg */
			wc = ff_uni2oem(wc, CODEPAGE);			/* Unicode ==> ANSI/OEM code */
			if (wc & 0x80) wc = ExCvt[wc & 0x7F];	/* Convert extended character to upper (SBCS) */
#else						/* DBCS cfg */
			wc = ff_uni2oem(ff_wtoupper(wc), CODEPAGE);	/* Unicode ==> Upper convert ==> ANSI/OEM code */
#endif
		}

		if (wc >= 0x100) {				/* Is this a DBC? */
			if (i >= ni - 1) {			/* Field overflow? */
				cf |= NS_LOSS | NS_LFN;
				i = ni; continue;		/* Next field */
			}
			dp->fn[i++] = (BYTE)(wc >> 8);	/* Put 1st byte */
		} else {						/* SBC */
			if (wc == 0 || chk_chr("+,;=[]", wc)) {	/* Replace illegal characters for SFN if needed */
				wc = '_'; cf |= NS_LOSS | NS_LFN;/* Lossy conversion */
			} else {
				if (IsUpper(wc)) {		/* ASCII upper case? */
					b |= 2;
				}
				if (IsLower(wc)) {		/* ASCII lower case? */
					b |= 1; wc -= 0x20;
				}
			}
		}
		dp->fn[i++] = (BYTE)wc;
	}

	if (dp->fn[0] == DDEM) dp->fn[0] = RDDEM;	/* If the first character collides with DDEM, replace it with RDDEM */

	if (ni == 8) b <<= 2;				/* Shift capital flags if no extension */
	if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03) cf |= NS_LFN;	/* LFN entry needs to be created if composite capitals */
	if (!(cf & NS_LFN)) {				/* When LFN is in 8.3 format without extended character, NT flags are created */
		if (b & 0x01) cf |= NS_EXT;		/* NT flag (Extension has small capital letters only) */
		if (b & 0x04) cf |= NS_BODY;	/* NT flag (Body has small capital letters only) */
	}

	dp->fn[NSFLAG] = cf;	/* SFN is created into dp->fn[] */

	return FR_OK;


#else	/* FF_USE_LFN : Non-LFN configuration */
	BYTE c, d, *sfn;
	UINT ni, si, i;
	const char *p;

	/* Create file name in directory form */
	p = *path; sfn = dp->fn;
	mem_set(sfn, ' ', 11);
	si = i = 0; ni = 8;
#if FF_FS_RPATH != 0
	if (p[si] == '.') { /* Is this a dot entry? */
		for (;;) {
			c = (BYTE)p[si++];
			if (c != '.' || si >= 3) break;
			sfn[i++] = c;
		}
		if (c != '/' && c != '\\' && c > ' ') return FR_INVALID_NAME;
		*path = p + si;								/* Return pointer to the next segment */
		sfn[NSFLAG] = (c <= ' ') ? NS_LAST | NS_DOT : NS_DOT;	/* Set last segment flag if end of the path */
		return FR_OK;
	}
#endif
	for (;;) {
		c = (BYTE)p[si++];				/* Get a byte */
		if (c <= ' ') break; 			/* Break if end of the path name */
		if (c == '/' || c == '\\') {	/* Break if a separator is found */
			while (p[si] == '/' || p[si] == '\\') si++;	/* Skip duplicated separator if exist */
			break;
		}
		if (c == '.' || i >= ni) {		/* End of body or field overflow? */
			if (ni == 11 || c != '.') return FR_INVALID_NAME;	/* Field overflow or invalid dot? */
			i = 8; ni = 11;				/* Enter file extension field */
			continue;
		}
#if FF_CODE_PAGE == 0
		if (ExCvt && c >= 0x80) {		/* Is SBC extended character? */
			c = ExCvt[c & 0x7F];		/* To upper SBC extended character */
		}
#elif FF_CODE_PAGE < 900
		if (c >= 0x80) {				/* Is SBC extended character? */
			c = ExCvt[c & 0x7F];		/* To upper SBC extended character */
		}
#endif
		if (dbc_1st(c)) {				/* Check if it is a DBC 1st byte */
			d = (BYTE)p[si++];			/* Get 2nd byte */
			if (!dbc_2nd(d) || i >= ni - 1) return FR_INVALID_NAME;	/* Reject invalid DBC */
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						/* SBC */
			if (chk_chr("\"*+,:;<=>\?[]|\x7F", c)) return FR_INVALID_NAME;	/* Reject illegal chrs for SFN */
			if (IsLower(c)) c -= 0x20;	/* To upper */
			sfn[i++] = c;
		}
	}
	*path = p + si;						/* Return pointer to the next segment */
	if (i == 0) return FR_INVALID_NAME;	/* Reject nul string */

	if (sfn[0] == DDEM) sfn[0] = RDDEM;	/* If the first character collides with DDEM, replace it with RDDEM */
	sfn[NSFLAG] = (c <= ' ') ? NS_LAST : 0;		/* Set last segment flag if end of the path */

	return FR_OK;
#endif /* FF_USE_LFN */
}