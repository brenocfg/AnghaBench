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
typedef  int WCHAR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  REGPROC_resize_char_buffer (int**,size_t*,size_t) ; 

__attribute__((used)) static void REGPROC_export_string(WCHAR **line_buf, DWORD *line_buf_size, DWORD *line_len, WCHAR *str, DWORD str_len)
{
    DWORD i, pos;
    DWORD extra = 0;

    REGPROC_resize_char_buffer(line_buf, line_buf_size, *line_len + str_len + 10);

    /* escaping characters */
    pos = *line_len;
    for (i = 0; i < str_len; i++) {
        WCHAR c = str[i];
        switch (c) {
        case '\n':
            extra++;
            REGPROC_resize_char_buffer(line_buf, line_buf_size, *line_len + str_len + extra);
            (*line_buf)[pos++] = '\\';
            (*line_buf)[pos++] = 'n';
            break;

        case '\\':
        case '"':
            extra++;
            REGPROC_resize_char_buffer(line_buf, line_buf_size, *line_len + str_len + extra);
            (*line_buf)[pos++] = '\\';
            /* Fall through */

        default:
            (*line_buf)[pos++] = c;
            break;
        }
    }
    (*line_buf)[pos] = '\0';
    *line_len = pos;
}