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
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MCIERR_BAD_INTEGER ; 
 int /*<<< orphan*/  MCIERR_PARSER_INTERNAL ; 
 int /*<<< orphan*/  MCIERR_UNRECOGNIZED_COMMAND ; 
#define  MCI_COMMAND_HEAD 137 
#define  MCI_CONSTANT 136 
 int MCI_DATA_SIZE ; 
#define  MCI_END_COMMAND 135 
#define  MCI_END_COMMAND_LIST 134 
#define  MCI_END_CONSTANT 133 
#define  MCI_FLAG 132 
 int /*<<< orphan*/  MCI_GetDWord (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  MCI_GetString (char**,char**) ; 
#define  MCI_INTEGER 131 
#define  MCI_RECT 130 
#define  MCI_RETURN 129 
#define  MCI_STRING 128 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int strlenW (scalar_t__) ; 
 scalar_t__ strncmpiW (char*,scalar_t__,int) ; 

__attribute__((used)) static	DWORD	MCI_ParseOptArgs(DWORD_PTR *data, int _offset, LPCWSTR lpCmd,
				 LPWSTR args, LPDWORD dwFlags)
{
    int		len, offset;
    const char* lmem;
    LPCWSTR     str;
    DWORD	dwRet, flg, cflg = 0;
    WORD	eid;
    BOOL	inCst, found;

    /* loop on arguments */
    while (*args) {
	lmem = (const char*)lpCmd;
	found = inCst = FALSE;
	offset = _offset;

	/* skip any leading white space(s) */
	while (*args == ' ') args++;
	TRACE("args=%s offset=%d\n", debugstr_w(args), offset);

	do { /* loop on options for command table for the requested verb */
	    str = (LPCWSTR)lmem;
	    lmem += ((len = strlenW(str)) + 1) * sizeof(WCHAR);
	    flg = *(const DWORD*)lmem;
	    eid = *(const WORD*)(lmem + sizeof(DWORD));
	    lmem += sizeof(DWORD) + sizeof(WORD);
            /* TRACE("\tcmd=%s inCst=%c eid=%04x\n", debugstr_w(str), inCst ? 'Y' : 'N', eid); */

	    switch (eid) {
	    case MCI_CONSTANT:
		inCst = TRUE;	cflg = flg;	break;
	    case MCI_END_CONSTANT:
		/* there may be additional integral values after flag in constant */
		if (inCst && MCI_GetDWord(&(data[offset]), &args)) {
		    *dwFlags |= cflg;
		}
		inCst = FALSE;	cflg = 0;
		break;
	    }

	    if (strncmpiW(args, str, len) == 0 &&
                ((eid == MCI_STRING && len == 0) || args[len] == 0 || args[len] == ' ')) {
		/* store good values into data[] */
		args += len;
		while (*args == ' ') args++;
		found = TRUE;

		switch (eid) {
		case MCI_COMMAND_HEAD:
		case MCI_RETURN:
		case MCI_END_COMMAND:
		case MCI_END_COMMAND_LIST:
		case MCI_CONSTANT: 	/* done above */
		case MCI_END_CONSTANT:  /* done above */
		    break;
		case MCI_FLAG:
		    *dwFlags |= flg;
		    break;
		case MCI_INTEGER:
		    if (inCst) {
			data[offset] |= flg;
			*dwFlags |= cflg;
			inCst = FALSE;
		    } else {
			*dwFlags |= flg;
			if (!MCI_GetDWord(&(data[offset]), &args)) {
			    return MCIERR_BAD_INTEGER;
			}
		    }
		    break;
		case MCI_RECT:
		    /* store rect in data (offset..offset+3) */
		    *dwFlags |= flg;
		    if (!MCI_GetDWord(&(data[offset+0]), &args) ||
			!MCI_GetDWord(&(data[offset+1]), &args) ||
			!MCI_GetDWord(&(data[offset+2]), &args) ||
			!MCI_GetDWord(&(data[offset+3]), &args)) {
			ERR("Bad rect %s\n", debugstr_w(args));
			return MCIERR_BAD_INTEGER;
		    }
		    break;
		case MCI_STRING:
		    *dwFlags |= flg;
		    if ((dwRet = MCI_GetString((LPWSTR*)&data[offset], &args)))
			return dwRet;
		    break;
		default:	ERR("oops\n");
		}
		/* exit inside while loop, except if just entered in constant area definition */
		if (!inCst || eid != MCI_CONSTANT) eid = MCI_END_COMMAND;
	    } else {
		/* have offset incremented if needed */
		switch (eid) {
		case MCI_COMMAND_HEAD:
		case MCI_RETURN:
		case MCI_END_COMMAND:
		case MCI_END_COMMAND_LIST:
		case MCI_CONSTANT:
		case MCI_FLAG:			break;
		case MCI_INTEGER:		if (!inCst) offset++;	break;
		case MCI_END_CONSTANT:
		case MCI_STRING:		offset++; break;
		case MCI_RECT:			offset += 4; break;
		default:			ERR("oops\n");
		}
	    }
	} while (eid != MCI_END_COMMAND);
	if (!found) {
	    WARN("Optarg %s not found\n", debugstr_w(args));
	    return MCIERR_UNRECOGNIZED_COMMAND;
	}
	if (offset == MCI_DATA_SIZE) {
	    ERR("Internal data[] buffer overflow\n");
	    return MCIERR_PARSER_INTERNAL;
	}
    }
    return 0;
}