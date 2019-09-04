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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
#define  REG_BINARY 133 
#define  REG_DWORD 132 
#define  REG_EXPAND_SZ 131 
#define  REG_MULTI_SZ 130 
#define  REG_NONE 129 
#define  REG_SZ 128 
 int /*<<< orphan*/  export_dword_data (int /*<<< orphan*/ **,void*) ; 
 int /*<<< orphan*/  export_hex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,size_t,void*,size_t) ; 
 int /*<<< orphan*/  export_newline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_string_data (int /*<<< orphan*/ **,void*,size_t) ; 
 size_t export_value_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void export_data(HANDLE hFile, WCHAR *value_name, DWORD value_len,
                        DWORD type, void *data, size_t size)
{
    WCHAR *buf = NULL;
    size_t line_len = export_value_name(hFile, value_name, value_len);

    switch (type)
    {
    case REG_SZ:
        export_string_data(&buf, data, size);
        break;
    case REG_DWORD:
        if (size)
        {
            export_dword_data(&buf, data);
            break;
        }
        /* fall through */
    case REG_NONE:
    case REG_EXPAND_SZ:
    case REG_BINARY:
    case REG_MULTI_SZ:
    default:
        export_hex_data(hFile, &buf, type, line_len, data, size);
        break;
    }

    if (size || type == REG_SZ)
    {
        write_file(hFile, buf);
        heap_free(buf);
    }

    export_newline(hFile);
}