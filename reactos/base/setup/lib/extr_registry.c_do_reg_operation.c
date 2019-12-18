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
typedef  unsigned char WCHAR ;
typedef  int ULONG ;
typedef  unsigned char* PWCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUNICODE_STRING ;
typedef  unsigned char* PUCHAR ;
typedef  int /*<<< orphan*/  PINFCONTEXT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int FLG_ADDREG_APPEND ; 
 int FLG_ADDREG_BINVALUETYPE ; 
 int FLG_ADDREG_DELVAL ; 
 int FLG_ADDREG_KEYONLY ; 
 int FLG_ADDREG_NOCLOBBER ; 
 int FLG_ADDREG_OVERWRITEONLY ; 
#define  FLG_ADDREG_TYPE_BINARY 133 
#define  FLG_ADDREG_TYPE_DWORD 132 
#define  FLG_ADDREG_TYPE_EXPAND_SZ 131 
 int FLG_ADDREG_TYPE_MASK ; 
#define  FLG_ADDREG_TYPE_MULTI_SZ 130 
#define  FLG_ADDREG_TYPE_NONE 129 
#define  FLG_ADDREG_TYPE_SZ 128 
 int /*<<< orphan*/  NtSetValueKey (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int REG_BINARY ; 
 int REG_DWORD ; 
 int REG_EXPAND_SZ ; 
 int REG_MULTI_SZ ; 
 int REG_NONE ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  SpInfGetBinaryField (int /*<<< orphan*/ ,int,unsigned char*,int,int*) ; 
 int SpInfGetFieldCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpInfGetMultiSzField (int /*<<< orphan*/ ,int,unsigned char*,int,int*) ; 
 int /*<<< orphan*/  SpInfGetStringField (int /*<<< orphan*/ ,int,unsigned char*,int,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int flags ; 
 int /*<<< orphan*/  hkey ; 
 int wcstoul (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
do_reg_operation(HANDLE KeyHandle,
                 PUNICODE_STRING ValueName,
                 PINFCONTEXT Context,
                 ULONG Flags)
{
  WCHAR EmptyStr = 0;
  ULONG Type;
  ULONG Size;

  if (Flags & FLG_ADDREG_DELVAL)  /* deletion */
    {
#if 0
      if (ValueName)
        {
          RegDeleteValueW( KeyHandle, ValueName );
        }
      else
        {
          RegDeleteKeyW( KeyHandle, NULL );
        }
#endif
      return TRUE;
    }

  if (Flags & FLG_ADDREG_KEYONLY)
    return TRUE;

#if 0
  if (Flags & (FLG_ADDREG_NOCLOBBER | FLG_ADDREG_OVERWRITEONLY))
    {
      BOOL exists = !RegQueryValueExW( hkey, ValueName, NULL, NULL, NULL, NULL );
      if (exists && (flags & FLG_ADDREG_NOCLOBBER))
        return TRUE;
      if (!exists & (flags & FLG_ADDREG_OVERWRITEONLY))
        return TRUE;
    }
#endif

  switch (Flags & FLG_ADDREG_TYPE_MASK)
    {
      case FLG_ADDREG_TYPE_SZ:
        Type = REG_SZ;
        break;

      case FLG_ADDREG_TYPE_MULTI_SZ:
        Type = REG_MULTI_SZ;
        break;

      case FLG_ADDREG_TYPE_EXPAND_SZ:
        Type = REG_EXPAND_SZ;
        break;

      case FLG_ADDREG_TYPE_BINARY:
        Type = REG_BINARY;
        break;

      case FLG_ADDREG_TYPE_DWORD:
        Type = REG_DWORD;
        break;

      case FLG_ADDREG_TYPE_NONE:
        Type = REG_NONE;
        break;

      default:
        Type = Flags >> 16;
        break;
    }

  if (!(Flags & FLG_ADDREG_BINVALUETYPE) ||
      (Type == REG_DWORD && SpInfGetFieldCount(Context) == 5))
    {
      PWCHAR Str = NULL;

      if (Type == REG_MULTI_SZ)
        {
          if (!SpInfGetMultiSzField(Context, 5, NULL, 0, &Size))
            Size = 0;

          if (Size)
            {
              Str = (WCHAR*) RtlAllocateHeap(ProcessHeap, 0, Size * sizeof(WCHAR));
              if (Str == NULL)
                return FALSE;

              SpInfGetMultiSzField(Context, 5, Str, Size, NULL);
            }

          if (Flags & FLG_ADDREG_APPEND)
            {
              if (Str == NULL)
                return TRUE;

              DPRINT1("append_multi_sz_value '%S' commented out, WHY??\n", ValueName);
//            append_multi_sz_value( hkey, value, str, size );

              RtlFreeHeap (ProcessHeap, 0, Str);
              return TRUE;
            }
          /* else fall through to normal string handling */
        }
      else
        {
          if (!SpInfGetStringField(Context, 5, NULL, 0, &Size))
            Size = 0;

          if (Size)
            {
              Str = (WCHAR*)RtlAllocateHeap(ProcessHeap, 0, Size * sizeof(WCHAR));
              if (Str == NULL)
                return FALSE;

              SpInfGetStringField(Context, 5, Str, Size, NULL);
            }
        }

      if (Type == REG_DWORD)
        {
          ULONG dw = Str ? wcstoul (Str, NULL, 0) : 0;

          DPRINT("setting dword %wZ to %lx\n", ValueName, dw);

          NtSetValueKey (KeyHandle,
                         ValueName,
                         0,
                         Type,
                         (PVOID)&dw,
                         sizeof(ULONG));
        }
      else
        {
          DPRINT("setting value %wZ to %S\n", ValueName, Str);

          if (Str)
            {
              NtSetValueKey (KeyHandle,
                             ValueName,
                             0,
                             Type,
                             (PVOID)Str,
                             Size * sizeof(WCHAR));
            }
          else
            {
              NtSetValueKey (KeyHandle,
                             ValueName,
                             0,
                             Type,
                             (PVOID)&EmptyStr,
                             sizeof(WCHAR));
            }
        }
      RtlFreeHeap (ProcessHeap, 0, Str);
    }
  else  /* get the binary data */
    {
      PUCHAR Data = NULL;

      if (!SpInfGetBinaryField(Context, 5, NULL, 0, &Size))
        Size = 0;

      if (Size)
        {
          Data = (unsigned char*) RtlAllocateHeap(ProcessHeap, 0, Size);
          if (Data == NULL)
            return FALSE;

          DPRINT("setting binary data %wZ len %lu\n", ValueName, Size);
          SpInfGetBinaryField(Context, 5, Data, Size, NULL);
        }

      NtSetValueKey (KeyHandle,
                     ValueName,
                     0,
                     Type,
                     (PVOID)Data,
                     Size);

      RtlFreeHeap (ProcessHeap, 0, Data);
    }

  return TRUE;
}