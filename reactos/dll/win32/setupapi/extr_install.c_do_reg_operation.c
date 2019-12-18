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
typedef  int /*<<< orphan*/  dw ;
typedef  scalar_t__ const WCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ const BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int FLG_ADDREG_APPEND ; 
 int FLG_ADDREG_BINVALUETYPE ; 
 int FLG_ADDREG_DELREG_BIT ; 
 int FLG_ADDREG_DELVAL ; 
 int FLG_ADDREG_KEYONLY ; 
 int FLG_ADDREG_KEYONLY_COMMON ; 
 int FLG_ADDREG_NOCLOBBER ; 
 int FLG_ADDREG_OVERWRITEONLY ; 
#define  FLG_ADDREG_TYPE_BINARY 133 
#define  FLG_ADDREG_TYPE_DWORD 132 
#define  FLG_ADDREG_TYPE_EXPAND_SZ 131 
 int FLG_ADDREG_TYPE_MASK ; 
#define  FLG_ADDREG_TYPE_MULTI_SZ 130 
#define  FLG_ADDREG_TYPE_NONE 129 
#define  FLG_ADDREG_TYPE_SZ 128 
 int FLG_DELREG_KEYONLY_COMMON ; 
 int FLG_DELREG_MULTI_SZ_DELSTRING ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ const* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  NtDeleteKey (int /*<<< orphan*/ ) ; 
 int REG_BINARY ; 
 int REG_DWORD ; 
 int REG_EXPAND_SZ ; 
 int REG_MULTI_SZ ; 
 int REG_NONE ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ,int,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  SetupGetBinaryField (int /*<<< orphan*/ *,int,scalar_t__ const*,int,int*) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetMultiSzFieldW (int /*<<< orphan*/ *,int,scalar_t__ const*,int,int*) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,scalar_t__ const*,int,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  append_multi_sz_value (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const*,int) ; 
 int debugstr_w (scalar_t__ const*) ; 
 int /*<<< orphan*/  delete_multi_sz_value (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const*) ; 
 int strtoulW (scalar_t__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL do_reg_operation( HKEY hkey, const WCHAR *value, INFCONTEXT *context, INT flags )
{
    DWORD type, size;

    if (flags & (FLG_ADDREG_DELREG_BIT | FLG_ADDREG_DELVAL))  /* deletion */
    {
        if (*value && !(flags & FLG_DELREG_KEYONLY_COMMON))
        {
            if ((flags & FLG_DELREG_MULTI_SZ_DELSTRING) == FLG_DELREG_MULTI_SZ_DELSTRING)
            {
                WCHAR *str;

                if (!SetupGetStringFieldW( context, 5, NULL, 0, &size ) || !size) return TRUE;
                if (!(str = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) ))) return FALSE;
                SetupGetStringFieldW( context, 5, str, size, NULL );
                delete_multi_sz_value( hkey, value, str );
                HeapFree( GetProcessHeap(), 0, str );
            }
            else RegDeleteValueW( hkey, value );
        }
        else NtDeleteKey( hkey );
        return TRUE;
    }

    if (flags & (FLG_ADDREG_KEYONLY|FLG_ADDREG_KEYONLY_COMMON)) return TRUE;

    if (flags & (FLG_ADDREG_NOCLOBBER|FLG_ADDREG_OVERWRITEONLY))
    {
        BOOL exists = !RegQueryValueExW( hkey, value, NULL, NULL, NULL, NULL );
        if (exists && (flags & FLG_ADDREG_NOCLOBBER)) return TRUE;
        if (!exists && (flags & FLG_ADDREG_OVERWRITEONLY)) return TRUE;
    }

    switch(flags & FLG_ADDREG_TYPE_MASK)
    {
    case FLG_ADDREG_TYPE_SZ:        type = REG_SZ; break;
    case FLG_ADDREG_TYPE_MULTI_SZ:  type = REG_MULTI_SZ; break;
    case FLG_ADDREG_TYPE_EXPAND_SZ: type = REG_EXPAND_SZ; break;
    case FLG_ADDREG_TYPE_BINARY:    type = REG_BINARY; break;
    case FLG_ADDREG_TYPE_DWORD:     type = REG_DWORD; break;
    case FLG_ADDREG_TYPE_NONE:      type = REG_NONE; break;
    default:                        type = flags >> 16; break;
    }

    if (!(flags & FLG_ADDREG_BINVALUETYPE) ||
        (type == REG_DWORD && SetupGetFieldCount(context) == 5))
    {
        static const WCHAR empty;
        WCHAR *str = NULL;

        if (type == REG_MULTI_SZ)
        {
            if (!SetupGetMultiSzFieldW( context, 5, NULL, 0, &size )) size = 0;
            if (size)
            {
                if (!(str = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) ))) return FALSE;
                SetupGetMultiSzFieldW( context, 5, str, size, NULL );
            }
            if (flags & FLG_ADDREG_APPEND)
            {
                if (!str) return TRUE;
                append_multi_sz_value( hkey, value, str, size );
                HeapFree( GetProcessHeap(), 0, str );
                return TRUE;
            }
            /* else fall through to normal string handling */
        }
        else
        {
            if (!SetupGetStringFieldW( context, 5, NULL, 0, &size )) size = 0;
            if (size)
            {
                if (!(str = HeapAlloc( GetProcessHeap(), 0, size * sizeof(WCHAR) ))) return FALSE;
                SetupGetStringFieldW( context, 5, str, size, NULL );
            }
        }

        if (type == REG_DWORD)
        {
            DWORD dw = str ? strtoulW( str, NULL, 0 ) : 0;
            TRACE( "setting dword %s to %x\n", debugstr_w(value), dw );
            RegSetValueExW( hkey, value, 0, type, (BYTE *)&dw, sizeof(dw) );
        }
        else
        {
            TRACE( "setting value %s to %s\n", debugstr_w(value), debugstr_w(str) );
            if (str) RegSetValueExW( hkey, value, 0, type, (BYTE *)str, size * sizeof(WCHAR) );
            else RegSetValueExW( hkey, value, 0, type, (const BYTE *)&empty, sizeof(WCHAR) );
        }
        HeapFree( GetProcessHeap(), 0, str );
        return TRUE;
    }
    else  /* get the binary data */
    {
        BYTE *data = NULL;

        if (!SetupGetBinaryField( context, 5, NULL, 0, &size )) size = 0;
        if (size)
        {
            if (!(data = HeapAlloc( GetProcessHeap(), 0, size ))) return FALSE;
            TRACE( "setting binary data %s len %d\n", debugstr_w(value), size );
            SetupGetBinaryField( context, 5, data, size, NULL );
        }
        RegSetValueExW( hkey, value, 0, type, data, size );
        HeapFree( GetProcessHeap(), 0, data );
        return TRUE;
    }
}