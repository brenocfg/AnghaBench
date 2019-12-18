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

/* Variables and functions */
 int /*<<< orphan*/  append_byte (unsigned char*,size_t*,size_t,char const) ; 
 int /*<<< orphan*/  hexval (char const) ; 
 int /*<<< orphan*/  isodigit (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 

__attribute__((used)) static const char *
parse_c_string(unsigned char *buf, size_t *buf_length,
               size_t buf_max, const char *line)
{
    size_t offset;

    if (*line != '\"')
        return line;
    else
        offset = 1;

    while (line[offset] && line[offset] != '\"') {
        if (line[offset] == '\\') {
            offset++;
            switch (line[offset]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                {
                    unsigned val = 0;

                    if (isodigit(line[offset]))
                        val = val * 8 + hexval(line[offset++]);
                    if (isodigit(line[offset]))
                        val = val * 8 + hexval(line[offset++]);
                    if (isodigit(line[offset]))
                        val = val * 8 + hexval(line[offset++]);
                    append_byte(buf, buf_length, buf_max, val);
                    continue;
                }
                break;
            case 'x':
                offset++;
                {
                    unsigned val = 0;

                    if (isxdigit(line[offset]))
                        val = val * 16 + hexval(line[offset++]);
                    if (isxdigit(line[offset]))
                        val = val * 16 + hexval(line[offset++]);
                    append_byte(buf, buf_length, buf_max, val);
                    continue;
                }
                break;

            case 'a':
                append_byte(buf, buf_length, buf_max, '\a');
                break;
            case 'b':
                append_byte(buf, buf_length, buf_max, '\b');
                break;
            case 'f':
                append_byte(buf, buf_length, buf_max, '\f');
                break;
            case 'n':
                append_byte(buf, buf_length, buf_max, '\n');
                break;
            case 'r':
                append_byte(buf, buf_length, buf_max, '\r');
                break;
            case 't':
                append_byte(buf, buf_length, buf_max, '\t');
                break;
            case 'v':
                append_byte(buf, buf_length, buf_max, '\v');
                break;
            default:
            case '\\':
                append_byte(buf, buf_length, buf_max, line[offset]);
                break;
            }
        } else
            append_byte(buf, buf_length, buf_max, line[offset]);

        offset++;
    }

    if (line[offset] == '\"')
        offset++;

    return line + offset;

}