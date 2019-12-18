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
struct in_src {int dummy; } ;
struct gc_arena {int dummy; } ;
struct buffer {int capacity; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSTR (struct buffer*) ; 
 int /*<<< orphan*/  M_FATAL ; 
 int OPTION_LINE_SIZE ; 
 struct buffer alloc_buf (int) ; 
 int /*<<< orphan*/  buf_clear (struct buffer*) ; 
 int /*<<< orphan*/  buf_copy (struct buffer*,struct buffer*) ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,char*) ; 
 int /*<<< orphan*/  buf_safe (struct buffer*,scalar_t__) ; 
 int /*<<< orphan*/  free_buf (struct buffer*) ; 
 scalar_t__ in_src_get (struct in_src*,char*,int) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  secure_memzero (char*,int) ; 
 char* string_alloc (int /*<<< orphan*/ ,struct gc_arena*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,scalar_t__) ; 

__attribute__((used)) static char *
read_inline_file(struct in_src *is, const char *close_tag, struct gc_arena *gc)
{
    char line[OPTION_LINE_SIZE];
    struct buffer buf = alloc_buf(8*OPTION_LINE_SIZE);
    char *ret;
    bool endtagfound = false;

    while (in_src_get(is, line, sizeof(line)))
    {
        char *line_ptr = line;
        /* Remove leading spaces */
        while (isspace(*line_ptr))
        {
            line_ptr++;
        }
        if (!strncmp(line_ptr, close_tag, strlen(close_tag)))
        {
            endtagfound = true;
            break;
        }
        if (!buf_safe(&buf, strlen(line)+1))
        {
            /* Increase buffer size */
            struct buffer buf2 = alloc_buf(buf.capacity * 2);
            ASSERT(buf_copy(&buf2, &buf));
            buf_clear(&buf);
            free_buf(&buf);
            buf = buf2;
        }
        buf_printf(&buf, "%s", line);
    }
    if (!endtagfound)
    {
        msg(M_FATAL, "ERROR: Endtag %s missing", close_tag);
    }
    ret = string_alloc(BSTR(&buf), gc);
    buf_clear(&buf);
    free_buf(&buf);
    secure_memzero(line, sizeof(line));
    return ret;
}