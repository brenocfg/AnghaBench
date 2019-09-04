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
typedef  char WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 char* GetMultiByteString (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REGPROC_export_binary (char**,int*,int*,int,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  REGPROC_export_string (char**,int*,int*,char*,int) ; 
 int /*<<< orphan*/  REGPROC_print_error () ; 
 int /*<<< orphan*/  REGPROC_resize_binary_buffer (int /*<<< orphan*/ **,int*,int) ; 
 int /*<<< orphan*/  REGPROC_resize_char_buffer (char**,int*,int) ; 
 int /*<<< orphan*/  REGPROC_write_line (int /*<<< orphan*/ *,char*,scalar_t__) ; 
#define  REG_BINARY 132 
#define  REG_DWORD 131 
#define  REG_EXPAND_SZ 130 
#define  REG_MULTI_SZ 129 
#define  REG_SZ 128 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  getAppName () ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strlenW (char*) ; 

__attribute__((used)) static void export_hkey(FILE *file, HKEY key,
                 WCHAR **reg_key_name_buf, DWORD *reg_key_name_size,
                 WCHAR **val_name_buf, DWORD *val_name_size,
                 BYTE **val_buf, DWORD *val_size,
                 WCHAR **line_buf, DWORD *line_buf_size,
                 BOOL unicode)
{
    DWORD max_sub_key_len;
    DWORD max_val_name_len;
    DWORD max_val_size;
    DWORD curr_len;
    DWORD i;
    BOOL more_data;
    LONG ret;
    WCHAR key_format[] = {'\r','\n','[','%','s',']','\r','\n',0};

    /* get size information and resize the buffers if necessary */
    if (RegQueryInfoKeyW(key, NULL, NULL, NULL, NULL,
                        &max_sub_key_len, NULL,
                        NULL, &max_val_name_len, &max_val_size, NULL, NULL
                       ) != ERROR_SUCCESS) {
        REGPROC_print_error();
    }
    curr_len = strlenW(*reg_key_name_buf);
    REGPROC_resize_char_buffer(reg_key_name_buf, reg_key_name_size,
                               max_sub_key_len + curr_len + 1);
    REGPROC_resize_char_buffer(val_name_buf, val_name_size,
                               max_val_name_len);
    REGPROC_resize_binary_buffer(val_buf, val_size, max_val_size);
    REGPROC_resize_char_buffer(line_buf, line_buf_size, lstrlenW(*reg_key_name_buf) + 4);
    /* output data for the current key */
    sprintfW(*line_buf, key_format, *reg_key_name_buf);
    REGPROC_write_line(file, *line_buf, unicode);

    /* print all the values */
    i = 0;
    more_data = TRUE;
    while(more_data) {
        DWORD value_type;
        DWORD val_name_size1 = *val_name_size;
        DWORD val_size1 = *val_size;
        ret = RegEnumValueW(key, i, *val_name_buf, &val_name_size1, NULL,
                           &value_type, *val_buf, &val_size1);
        if (ret == ERROR_MORE_DATA) {
            /* Increase the size of the buffers and retry */
            REGPROC_resize_char_buffer(val_name_buf, val_name_size, val_name_size1);
            REGPROC_resize_binary_buffer(val_buf, val_size, val_size1);
        } else if (ret != ERROR_SUCCESS) {
            more_data = FALSE;
            if (ret != ERROR_NO_MORE_ITEMS) {
                REGPROC_print_error();
            }
        } else {
            DWORD line_len;
            i++;

            if ((*val_name_buf)[0]) {
                const WCHAR val_start[] = {'"','%','s','"','=',0};

                line_len = 0;
                REGPROC_export_string(line_buf, line_buf_size, &line_len, *val_name_buf, lstrlenW(*val_name_buf));
                REGPROC_resize_char_buffer(val_name_buf, val_name_size, lstrlenW(*line_buf) + 1);
                lstrcpyW(*val_name_buf, *line_buf);

                line_len = 3 + lstrlenW(*val_name_buf);
                REGPROC_resize_char_buffer(line_buf, line_buf_size, line_len);
                sprintfW(*line_buf, val_start, *val_name_buf);
            } else {
                const WCHAR std_val[] = {'@','=',0};
                line_len = 2;
                REGPROC_resize_char_buffer(line_buf, line_buf_size, line_len);
                lstrcpyW(*line_buf, std_val);
            }

            switch (value_type) {
            case REG_SZ:
            {
                WCHAR* wstr = (WCHAR*)*val_buf;

                if (val_size1 < sizeof(WCHAR) || val_size1 % sizeof(WCHAR) ||
                    wstr[val_size1 / sizeof(WCHAR) - 1]) {
                    REGPROC_export_binary(line_buf, line_buf_size, &line_len, value_type, *val_buf, val_size1, unicode);
                } else {
                    const WCHAR start[] = {'"',0};
                    const WCHAR end[] = {'"','\r','\n',0};
                    DWORD len;

                    len = lstrlenW(start);
                    REGPROC_resize_char_buffer(line_buf, line_buf_size, line_len + len);
                    lstrcpyW(*line_buf + line_len, start);
                    line_len += len;

                    /* At this point we know wstr is '\0'-terminated
                     * so we can subtract 1 from the size
                     */
                    REGPROC_export_string(line_buf, line_buf_size, &line_len, wstr, val_size1 / sizeof(WCHAR) - 1);

                    REGPROC_resize_char_buffer(line_buf, line_buf_size, line_len + lstrlenW(end));
                    lstrcpyW(*line_buf + line_len, end);
                }
                break;
            }

            case REG_DWORD:
            {
                WCHAR format[] = {'d','w','o','r','d',':','%','0','8','x','\r','\n',0};

                REGPROC_resize_char_buffer(line_buf, line_buf_size, line_len + 15);
                sprintfW(*line_buf + line_len, format, *((DWORD *)*val_buf));
                break;
            }

            default:
            {
                char* key_nameA = GetMultiByteString(*reg_key_name_buf);
                char* value_nameA = GetMultiByteString(*val_name_buf);
                fprintf(stderr,"%S: warning - unsupported registry format '%ld', "
                        "treat as binary\n",
                        getAppName(), value_type);
                fprintf(stderr,"key name: \"%s\"\n", key_nameA);
                fprintf(stderr,"value name:\"%s\"\n\n", value_nameA);
                HeapFree(GetProcessHeap(), 0, key_nameA);
                HeapFree(GetProcessHeap(), 0, value_nameA);
            }
                /* falls through */
            case REG_EXPAND_SZ:
            case REG_MULTI_SZ:
                /* falls through */
            case REG_BINARY:
                REGPROC_export_binary(line_buf, line_buf_size, &line_len, value_type, *val_buf, val_size1, unicode);
            }
            REGPROC_write_line(file, *line_buf, unicode);
        }
    }

    i = 0;
    more_data = TRUE;
    (*reg_key_name_buf)[curr_len] = '\\';
    while(more_data) {
        DWORD buf_size = *reg_key_name_size - curr_len - 1;

        ret = RegEnumKeyExW(key, i, *reg_key_name_buf + curr_len + 1, &buf_size,
                           NULL, NULL, NULL, NULL);
        if (ret == ERROR_MORE_DATA) {
            /* Increase the size of the buffer and retry */
            REGPROC_resize_char_buffer(reg_key_name_buf, reg_key_name_size, curr_len + 1 + buf_size);
        } else if (ret != ERROR_SUCCESS) {
            more_data = FALSE;
            if (ret != ERROR_NO_MORE_ITEMS) {
                REGPROC_print_error();
            }
        } else {
            HKEY subkey;

            i++;
            if (RegOpenKeyW(key, *reg_key_name_buf + curr_len + 1,
                           &subkey) == ERROR_SUCCESS) {
                export_hkey(file, subkey, reg_key_name_buf, reg_key_name_size,
                            val_name_buf, val_name_size, val_buf, val_size,
                            line_buf, line_buf_size, unicode);
                RegCloseKey(subkey);
            } else {
                REGPROC_print_error();
            }
        }
    }
    (*reg_key_name_buf)[curr_len] = '\0';
}